/* serverlookup.c - Illustrates how servers lookup hosts and ports */

#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char ** argv) {
    struct addrinfo hints, * addr;
    const char * service = argv[1];
    int rc;

    if (argc != 3) {
        fprintf(stderr, "exactly one argument is needed\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));			

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
    if ((rc = getaddrinfo(NULL, service, &hints, &addr)))
	fprintf(stderr, "lookup failed\n");
    else
	freeaddrinfo(addr);				

    return 0;
}
