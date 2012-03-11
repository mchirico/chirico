/* Copyright GPL Mike Chirico mchirico@users.sourceforge.net
   Updated: Mon Jan  8 13:39:57 EST 2007



*/

#include <stdlib.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include "wrapper.h"


#define SA      struct sockaddr
#define MAXLINE 4096

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ         1024	/* 2nd argument to listen() */

/* for asyc_write */
struct S_Buf {
	int conn;
	char *s;
};

static void *asyc_write(void *arg)
{
	int conn;
	char *s;

	conn = ((struct S_Buf *) arg)->conn;
	s = ((struct S_Buf *) arg)->s;

	//fprintf(stderr, "asyc_write s.len=%d ->%s<-\n", strlen(s), s);
	write(conn, s, strlen(s));

	free(s);
	free(arg);
	Pthread_detach(pthread_self());
	return (NULL);
}


static void *asyc_read(void *arg)
{
	int conn, n;
	char s[MAXLINE+1];

	conn = *((int *) arg);
	Pthread_detach(pthread_self());
	while ((n = read(conn, s, MAXLINE)) > 0){
	  s[n]='\0';
		fprintf(stderr,
			"%s",s);


	}

	fprintf(stderr, "Connection Terminated");


	//free(s); -- no not here, didn't allocate
	//free(arg); -- no not here, didn't allocate

	return (NULL);
}

void process_stuffC(FILE * fp, int sockfd)
{
	struct S_Buf *s_b;

	pthread_t t;

	char sendline[MAXLINE + 1];

	Pthread_create(&t, NULL, &asyc_read, &sockfd);

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		//write(sockfd, sendline, strlen(sendline));
		s_b = (struct S_Buf *) malloc(sizeof(struct S_Buf));
		s_b->s = (char *) malloc(sizeof(char) * sizeof(sendline));
		strcpy(s_b->s, sendline);
		s_b->conn = sockfd;
		Pthread_create(&t, NULL, &asyc_write, s_b);
	}
}





int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		fprintf(stderr, "usage: client <IPaddress>\n");
		fprintf(stderr, "Try: ./client localhost\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(10000);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	fprintf(stderr, "Type one the following. Exactly as shown:\n");
	fprintf(stderr, "READFILE|\n");
	fprintf(stderr, "RESET|\n");
	fprintf(stderr, "ECHO|<some text>\n");
	fprintf(stderr, "WRITE|<0-4>   <some text>\n");
	fprintf(stderr, "STAT| Lists connections \n");
	fprintf(stderr, "May need to hit return if blocking\n\n\n");


	process_stuffC(stdin, sockfd);
	exit(0);

}
