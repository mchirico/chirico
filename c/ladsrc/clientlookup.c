/* clientlookup.c - Illustrates how clients lookup hosts and ports */

#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char ** argv) {
    struct addrinfo hints, * addr;
    const char * host = argv[1], * service = argv[2];
    int rc;

    if (argc != 3) {
        fprintf(stderr, "exactly two arguments are needed\n");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));			

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG;
    if ((rc = getaddrinfo(host, service, &hints, &addr)))
	fprintf(stderr, "lookup failed\n");
    else
	freeaddrinfo(addr);				

    return 0;
}
