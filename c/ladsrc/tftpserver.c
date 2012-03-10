/* tftpserver.c - Minimal tftp server to illustrate UDP sockets */

/* This is a partial implementation of tftp. It doesn't ever time 
   out or resend packets, and it doesn't handle unexpected events 
   very well. */

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include "sockutil.h"          /* some utility functions */

#define RRQ	1	       /* read request */	    
#define DATA	3	       /* data block */
#define ACK	4	       /* acknowledgement */
#define ERROR	5	       /* error occured */

/* tftp error codes */
#define FILE_NOT_FOUND	1

struct tftpPacket {			
    short opcode;

    union {
	char bytes[514];       /* largest packet we can handle has 2
				  bytes for block number and 512 
				  for data */
	struct {
	    short code;
	    char message[200];
	} error;

	struct {
	    short block;
	    char bytes[512];
	} data;

	struct {
	    short block;
	} ack;
    } u;
};					

void sendError(int s, int errorCode) {
    struct tftpPacket err;
    int size;

    err.opcode = htons(ERROR);

    err.u.error.code = htons(errorCode);   /* file not found */
    switch (errorCode) {
    case FILE_NOT_FOUND:
	strcpy(err.u.error.message, "file not found");
	break;
    }

    /* 2 byte opcode, 2 byte error code, the message and a '\0' */
    size = 2 + 2 + strlen(err.u.error.message) + 1;
    if (send(s, &err, size, 0) != size) 
	die("error send");
}

void handleRequest(struct addrinfo tftpAddr, 
		   struct sockaddr remote, int remoteLen, 
		   struct tftpPacket request) {
    char * fileName;
    char * mode;
    int fd;
    int s;
    int size;
    int sizeRead;
    struct tftpPacket data, response;
    int blockNum = 0;

    request.opcode = ntohs(request.opcode);
    if (request.opcode != RRQ) die("bad opcode");

    fileName = request.u.bytes;
    mode = fileName + strlen(fileName) + 1;

    /* we only support bin mode */
    if (strcmp(mode, "octet"))  {
	fprintf(stderr, "bad mode %s\n", mode);
	exit(1);
    }

    /* we want to send using a socket of the same family and type
       we started with, */
    if ((s = socket(tftpAddr.ai_family, tftpAddr.ai_socktype,   
		    tftpAddr.ai_protocol)) < 0)
	die("send socket");

    /* set the remote end of the socket to the address which 
       initiated this connection */
    if (connect(s, &remote, remoteLen))
	die("connect");

    if ((fd = open(fileName, O_RDONLY)) < 0) {
	sendError(s, FILE_NOT_FOUND);
	close(s);
	return ;
    }

    data.opcode = htons(DATA);
    while ((size = read(fd, data.u.data.bytes, 512)) > 0) {
	data.u.data.block = htons(++blockNum);

	/* size is 2 byte opcode, 2 byte block number, data */
	size += 4;
	if (send(s, &data, size, 0) != size)
	    die("data send");

	sizeRead = recv(s, &response, sizeof(response), 0);
	if (sizeRead < 0) die("recv ack");

	response.opcode = ntohs(response.opcode);
	if (response.opcode != ACK) {
	    fprintf(stderr, "unexpected opcode in response\n");
	    exit(1);
	}

	response.u.ack.block = ntohs(response.u.ack.block);
	if (response.u.ack.block != blockNum) {
	    fprintf(stderr, "received ack of wrong block\n");
	    exit(1);
	}

	/* if the block we just sent had less than 512 data 
	   bytes, we're done */
	if (size < 516) break;
    }

    close(s);
}

int main(int argc, char ** argv) {
    struct addrinfo hints, * addr;
    char * portAddress = "tftp";
    int s;
    int rc;
    int bytes, fromLen;
    struct sockaddr from;
    struct tftpPacket packet;

    if (argc > 2) {
	fprintf(stderr, "usage: tftpserver [port]\n");
	exit(1);
    }

    if (argv[1]) portAddress = argv[1];

    memset(&hints, 0, sizeof(hints));			

    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
    if ((rc = getaddrinfo(NULL, portAddress, &hints, &addr)))
	fprintf(stderr, "lookup of port %s failed\n", 
		portAddress);

    if ((s = socket(addr->ai_family, addr->ai_socktype, 
		    addr->ai_protocol)) < 0)
	die("socket");

    if (bind(s, addr->ai_addr, addr->ai_addrlen))
	die("bind");					

    /* The main loop waits for a tftp request, handles the 
       request, and then waits for another one. */
    while (1) {
	bytes = recvfrom(s, &packet, sizeof(packet), 0, &from, 
			 &fromLen);
	if (bytes < 0) die("recvfrom");

	/* if we forked before calling handleRequest() and had 
	   the child exit after the function returned, this server 
	   would work perfectly well as a concurrent tftp server */
	handleRequest(*addr, from, fromLen, packet);	    
    }
}
