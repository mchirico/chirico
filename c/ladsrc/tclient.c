/* tclient.c - Simple TCP/IP tclient */

/* Connect to the server whose hostname or IP is given as an
   argument, at port 4321. Once connected, copy everything on
   stdin to the socket, then exit. */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockutil.h"          /* some utility functions */

int main(int argc, const char ** argv) {
    struct addrinfo hints, * addr;
    struct sockaddr_in * addrInfo;
    int rc;
    int sock;

    if (argc != 2) {
        fprintf(stderr, "only a single argument is supported\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG;
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &addr))) {
	fprintf(stderr, "hostname lookup failed: %s\n", 
		gai_strerror(rc));
	return 1;
    }

    /* this lets us access the sin_family and sin_port (which are
       in the same place as sin6_family and sin6_port */
    addrInfo = (struct sockaddr_in *) addr->ai_addr;

    if ((sock = socket(addrInfo->sin_family, addr->ai_socktype, 
		       addr->ai_protocol)) < 0)
        die("socket");

    addrInfo->sin_port = htons(4321);

    if (connect(sock, (struct sockaddr *) addrInfo, 
		addr->ai_addrlen))
        die("connect");

    freeaddrinfo(addr);

    copyData(0, sock);

    close(sock);
    
    return 0;
}
