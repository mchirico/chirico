/* reverselookup.c - Demonstrates features of \codefn{getnameinfo()} */

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Called when errors occur during command line processing; this 
   displays a brief usage message and exits */
void usage(void) {
    fprintf(stderr, "usage: reverselookup [--numerichost] "
	    "[--numericserv] [--namereqd] [--udp]\n");
    fprintf(stderr, "                     [--nofqdn] "
	    "[--service <service>] [--host <hostname>]\n");
    exit(1);
}

int main(int argc, const char ** argv) {
    int flags;
    const char * hostAddress = NULL;
    const char * serviceAddress = NULL;
    struct sockaddr_in addr4;
    struct sockaddr_in6 addr6;
    struct sockaddr * addr = (struct sockaddr *) &addr4;
    int addrLen = sizeof(addr4);
    int rc;
    int portNum = 0;
    const char ** ptr;
    char hostName[1024];
    char serviceName[256];

    /* clear the flags */
    flags = 0;

    /* parse the command line arguments, skipping over argv[0] */
    ptr = argv + 1;
    while (*ptr && *ptr[0] == '-') {
	if (!strcmp(*ptr, "--numerichost")) {
	    flags |= NI_NUMERICHOST;
	} else if (!strcmp(*ptr, "--numericserv")) {
	    flags |= NI_NUMERICSERV;
	} else if (!strcmp(*ptr, "--namereqd")) {
	    flags |= NI_NAMEREQD;
	} else if (!strcmp(*ptr, "--nofqdn")) {
	    flags |= NI_NOFQDN;
	} else if (!strcmp(*ptr, "--udp")) {
	    flags |= NI_DGRAM;
	} else if (!strcmp(*ptr, "--host")) {
	    ptr++;
	    if (!*ptr) usage();
	    hostAddress = *ptr;
	} else if (!strcmp(*ptr, "--service")) {
	    ptr++;
	    if (!*ptr) usage();
	    serviceAddress = *ptr;
	} else
	    usage();

	ptr++;
    }

    /* we need a hostAddress, serviceAddress, or both */
    if (!hostAddress && !serviceAddress)
	usage();

    if (serviceAddress) {
	char * end;

	portNum = htons(strtol(serviceAddress, &end, 0));
	if (*end) {
	    fprintf(stderr, "failed to convert %s to a number\n", 
		    serviceAddress);
	    return 1;
	}
    }

    if (!hostAddress) {				
	addr4.sin_family = AF_INET;
	addr4.sin_port = portNum;
    } else if (!strchr(hostAddress, ':')) {
	/* If a colon appears in the hostAddress, assume IPv6. 
	   Otherwise, it must be IPv4 */

	if (inet_pton(AF_INET, hostAddress, 
		      &addr4.sin_addr) <= 0) {
	    fprintf(stderr, "error converting IPv4 address %s\n", 
		    hostAddress);
	    return 1;
	}

	addr4.sin_family = AF_INET;
	addr4.sin_port = portNum;
    } else {

	memset(&addr6, 0, sizeof(addr6));

	if (inet_pton(AF_INET6, hostAddress, 
		      &addr6.sin6_addr) <= 0) {
	    fprintf(stderr, "error converting IPv6 address %s\n", 
		    hostAddress);
	    return 1;
	}

	addr6.sin6_family = AF_INET6;
	addr6.sin6_port = portNum;
	addr = (struct sockaddr *) &addr6;
	addrLen = sizeof(addr6);
    }						

    if (!serviceAddress) {
	rc = getnameinfo(addr, addrLen, hostName, sizeof(hostName), 
			 NULL, 0,  flags);
    } else if (!hostAddress) {
	rc = getnameinfo(addr, addrLen, NULL, 0, 
			 serviceName, sizeof(serviceName), flags);
    } else {
	rc = getnameinfo(addr, addrLen, hostName, sizeof(hostName),
			 serviceName, sizeof(serviceName), flags);
    }

    if (rc) {
	fprintf(stderr, "reverse lookup failed: %s\n", 
		gai_strerror(rc));
	return 1;
    }

    if (hostAddress)
	printf("hostname: %s\n", hostName);
    if (serviceAddress)
	printf("service name: %s\n", serviceName);

    return 0;
}
