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
#define MAXLINE 8012
#define MAXSUB  MAXLINE - 1024


#define LISTENQ         1024

extern int h_errno;

ssize_t process_http(int sockfd, char *host, char *page, char *poststr)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	ssize_t n;
	snprintf(sendline, MAXSUB,
		 "POST %s HTTP/1.0\r\n"
		 "Host: %s\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %d\r\n\r\n"
		 "%s", page, host, strlen(poststr), poststr);

	write(sockfd, sendline, strlen(sendline));
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = '\0';
		printf("%s", recvline);
	}
	return n;

}
int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	static char s[MAXLINE];

	if (argc == 2 )
	  snprintf(s,MAXLINE,"action=ActionDelete&hash=3ad540e4c39f54d0d138c60d66c1d923&ActionTag=%s&ActionRows=10&\r\n",argv[1]);
	else if (argc == 3 )
	  snprintf(s,MAXLINE,"action=ActionDelete&hash=3ad540e4c39f54d0d138c60d66c1d923&ActionTag=%s&ActionRows=%s&\r\n",argv[1],argv[2]);
	else
	  snprintf(s,MAXLINE,"action=ActionDelete&hash=3ad540e4c39f54d0d138c60d66c1d923&ActionTag=%s&ActionRows=20&\r\n","2017-06-01 10:11:46.693103");



	char **pptr;
	//********** You can change. Puy any values here *******
	char *hname = "souptonutsmc.appspot.com";
	char *page = "/cron/fireAction";
	/*	char *poststr = "action=ActionDelete&hash=3ad540e4c39f54d0d138c60d66c1d923&\r\n";  */
	char *poststr = s; 
	fprintf(stderr,"poststr=%s\n",poststr);
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
	servaddr.sin_port = htons(80);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	process_http(sockfd, hname, page, poststr);
	close(sockfd);
	exit(0);

}
