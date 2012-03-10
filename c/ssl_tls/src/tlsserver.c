/*  Copyright (C) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>



    References:
        http://www.faqs.org/rfcs/rfc2821.html

     bcc - blind carbon copy
        http://www.faqs.org/rfcs/rfc822.html

     OpenSSL Command-Line HOWTO
        http://www.madboa.com/geek/openssl/

     OpenSSL Programming examples
        http://www.opensslbook.com/code.html

     TLS
        http://www.faqs.org/rfcs/rfc3207.html

     IMAP
        http://www.faqs.org/rfcs/rfc3501.html

*/


#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200


#define LISTENQ         1024

extern int h_errno;

ssize_t process_smtp(int sockfd, char *host, char *page, char *poststr)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	ssize_t n;


	/* Beginning of Envelope */
	snprintf(sendline, MAXSUB, "HELO squeezel.com\r\n");
	write(sockfd, sendline, strlen(sendline));
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	printf("%s", recvline);

	snprintf(sendline, MAXSUB,
		 "MAIL FROM: bozo.clown@jefferson.edu\r\n");
	write(sockfd, sendline, strlen(sendline));
	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	printf("%s", recvline);


	snprintf(sendline, MAXSUB,
		 "RCPT TO: chirico@squeezel.squeezel.com\r\n");
	write(sockfd, sendline, strlen(sendline));


	snprintf(sendline, MAXSUB,
		 "RCPT TO: mchirico@squeezel.squeezel.com\r\n");
	write(sockfd, sendline, strlen(sendline));

	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	printf("%s", recvline);


	/* End of Envelope */


	snprintf(sendline, MAXSUB, "DATA\r\n");
	write(sockfd, sendline, strlen(sendline));

	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	printf("%s", recvline);



	/* Header */
	snprintf(sendline, MAXSUB,
		 "From: Bozo.Clown@jefferson.edu\r\nTo: chirico@squeezel.squeezel.com\r\nbcc: mchirico@squeezel.squeezel.com\r\n");
	write(sockfd, sendline, strlen(sendline));

	snprintf(sendline, MAXSUB,
		 "bcc: chirico@squeezel.squeezel.com\r\n");
	write(sockfd, sendline, strlen(sendline));


	/* Sample bcc */
	snprintf(sendline, MAXSUB,
		 "Subject: This is bcc test send 13\r\n\r\n");
	write(sockfd, sendline, strlen(sendline));






	snprintf(sendline, MAXSUB,
		 "mchirico@squeezel.squeezel.com is the bcc in this message.\n");
	write(sockfd, sendline, strlen(sendline));

	snprintf(sendline, MAXSUB,
		 "\ndoes mchirico show up in the header?");
	write(sockfd, sendline, strlen(sendline));


	snprintf(sendline, MAXSUB, "\r\n.\r\n");
	write(sockfd, sendline, strlen(sendline));

	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	printf("%s", recvline);




	return n;

}
int main(void)
{
	int sockfd;
	struct sockaddr_in servaddr;

	char **pptr;
	//********** You can change. Puy any values here *******
	char *hname = "squeezel.squeezel.com";
	char *page = "";
	char *poststr = "HELO squeezel.com\r\n";
	//*******************************************************

	char str[50];
	struct hostent *hptr;
	if ((hptr = gethostbyname(hname)) == NULL) {
		fprintf(stderr, " gethostbyname error for host: %s: %s",
			hname, hstrerror(h_errno));
		exit(1);
	}
	printf("hostname: %s\n", hptr->h_name);
	if (hptr->h_addrtype == AF_INET
	    && (pptr = hptr->h_addr_list) != NULL) {
		printf("address: %s\n",
		       inet_ntop(hptr->h_addrtype, *pptr, str,
				 sizeof(str)));
	} else {
		fprintf(stderr, "Error call inet_ntop \n");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(25);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	process_smtp(sockfd, hname, page, poststr);
	close(sockfd);
	exit(0);

}
