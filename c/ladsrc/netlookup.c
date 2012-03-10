/* netlookup.c - Demonstrates the features of \codefn{getaddrinfo()} */

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Called when errors occur during command line processing; 
   this displays a brief usage message and exits */
void usage(void) {
    fprintf(stderr, "usage: netlookup [--stream] [--dgram] "
	    "[--ipv4] [--ipv6] [--name] [--udp]\n");
    fprintf(stderr, "                 [--tcp] [--cfg] "
	    "[--service <service>] [--host <hostname>]\n");
    exit(1);
}

int main(int argc, const char ** argv) {
    struct addrinfo * addr, * result;
    const char ** ptr;
    int rc;
    struct addrinfo hints;
    const char * serviceName = NULL;
    const char * hostName = NULL;

    /* clear the hints structure */
    memset(&hints, 0, sizeof(hints));

    /* parse the command line arguments, skipping over argv[0] 
    
       The hints structure, serviceName, and hostName will be 
       filled in based on which arguments are present. */
    ptr = argv + 1;
    while (*ptr && *ptr[0] == '-') {
	if (!strcmp(*ptr, "--ipv4"))
	    hints.ai_family = PF_INET;
	else if (!strcmp(*ptr, "--ipv6"))
	    hints.ai_family = PF_INET6;
	else if (!strcmp(*ptr, "--stream"))
	    hints.ai_socktype = SOCK_STREAM;
	else if (!strcmp(*ptr, "--dgram"))
	    hints.ai_socktype = SOCK_DGRAM;
	else if (!strcmp(*ptr, "--name"))
	    hints.ai_flags |= AI_CANONNAME;
	else if (!strcmp(*ptr, "--cfg"))
	    hints.ai_flags |= AI_ADDRCONFIG;
	else if (!strcmp(*ptr, "--tcp")) {
	    hints.ai_protocol = IPPROTO_TCP;
	} else if (!strcmp(*ptr, "--udp")) {
	    hints.ai_protocol = IPPROTO_UDP;
	} else if (!strcmp(*ptr, "--host")) {
	    ptr++;
	    if (!*ptr) usage();
	    hostName = *ptr;
	} else if (!strcmp(*ptr, "--service")) {
	    ptr++;
	    if (!*ptr) usage();
	    serviceName = *ptr;
	} else
	    usage();

	ptr++;
    }

    /* we need a hostName, serviceName, or both */
    if (!hostName && !serviceName)
	usage();

    if ((rc = getaddrinfo(hostName, serviceName, &hints, 
			  &result))) {
	fprintf(stderr, "service lookup failed: %s\n", 
		gai_strerror(rc));
	return 1;
    }

    /* walk through the linked list, displaying all results */
    addr = result;
    while (addr) {
	switch (addr->ai_family) {
	    case PF_INET:	printf("IPv4"); 
				break;
	    case PF_INET6:	printf("IPv6"); 
				break;
	    default:		printf("(%d)", addr->ai_family); 
				break;
	}

	switch (addr->ai_socktype) {
	    case SOCK_STREAM:	printf("\tstream"); 
				break;
	    case SOCK_DGRAM:	printf("\tdgram"); 
				break;
	    case SOCK_RAW:	printf("\traw  "); 
				break;
	    default:		printf("\t(%d)", 
				       addr->ai_socktype); 
				break;
	}

	if (addr->ai_family == PF_INET || 
		addr->ai_family == PF_INET6)
	    switch (addr->ai_protocol) {
		case IPPROTO_TCP:   printf("\ttcp"); 
				    break;
		case IPPROTO_UDP:   printf("\tudp"); 
				    break;
		case IPPROTO_RAW:   printf("\traw"); 
				    break;
		default:	    printf("\t(%d)", 
					   addr->ai_protocol);
				    break;
	    }
	else
	    printf("\t");

	/* display information for both IPv4 and IPv6 addresses */

	if (addr->ai_family == PF_INET) {	    
	    struct sockaddr_in * inetaddr = (void *) addr->ai_addr;
	    char nameBuf[INET_ADDRSTRLEN];

	    if (serviceName)
		printf("\tport %d", ntohs(inetaddr->sin_port));

	    if (hostName)
		printf("\thost %s", 
		       inet_ntop(AF_INET, &inetaddr->sin_addr,
				 nameBuf, sizeof(nameBuf)));
	} else if (addr->ai_family == PF_INET6) {
	    struct sockaddr_in6 * inetaddr = 
				    (void *) addr->ai_addr;
	    char nameBuf[INET6_ADDRSTRLEN];

	    if (serviceName)
		printf("\tport %d", ntohs(inetaddr->sin6_port));

	    if (hostName)
		printf("\thost %s", 
			inet_ntop(AF_INET6, &inetaddr->sin6_addr,
				  nameBuf, sizeof(nameBuf)));
	}					

	if (addr->ai_canonname)
	    printf("\tname %s", addr->ai_canonname);

	printf("\n");

	addr = addr->ai_next;
    }

    /* free the results of getaddrinfo() */
    freeaddrinfo(result);

    return 0;
}
