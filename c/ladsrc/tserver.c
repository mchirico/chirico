/* tserver.c - Simple TCP/IP server */

/* Waits for a connection on port 4321. Once a connection has been
   established, copy data from the socket to stdout until the other 
   end closes the connection, and then wait for another connection 
   to the socket. */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sockutil.h"          /* some utility functions */

int main(void) {
    int sock, conn, i, rc;
    struct sockaddr address;
    size_t addrLength = sizeof(address);
    struct addrinfo hints, * addr;

    memset(&hints, 0, sizeof(hints));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    if ((rc = getaddrinfo(NULL, "4321", &hints, &addr))) {
	fprintf(stderr, "hostname lookup failed: %s\n", 
		gai_strerror(rc));
	return 1;
    }

    if ((sock = socket(addr->ai_family, addr->ai_socktype, 
		       addr->ai_protocol)) < 0)
        die("socket");

    /* Let the kernel reuse the socket address. This lets us run
       twice in a row, without waiting for the (ip, port) tuple
       to time out. */
    i = 1;                                      
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)); 

    if (bind(sock, addr->ai_addr, addr->ai_addrlen))
        die("bind");

    freeaddrinfo(addr);

    if (listen(sock, 5))
        die("listen");

    while ((conn = accept(sock, (struct sockaddr *) &address, 
                          &addrLength)) >= 0) {
        printf("---- getting data\n");
        copyData(conn, 1);
        printf("---- done\n");
        close(conn);
    }

    if (conn < 0) 
        die("accept");
    
    close(sock);
    return 0;
}
