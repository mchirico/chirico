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

#include <syslog.h>
#include <sys/time.h>
#include <time.h>


#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200


#define LISTENQ         1024

extern int h_errno;


int rate(int dsec, int dusec)
{
	char buffer[30];
	struct timeval tv;
	time_t curtime;
	gettimeofday(&tv, NULL);

	double ct = 0;
	double dt = 0;
	static double st = 0.0;

	ct = (double) tv.tv_sec + (double) tv.tv_usec / 1000000;
	dt = (double) dsec + (double) dusec / 1000000;


	if (st == 0.0) {
		st = ct;
		return 1;
	} else {
		if ((st + dt) <= ct) {
			st = ct;
			return 1;
		}
	}

	return 0;

}



ssize_t process_http(int sockfd, char *host, char *page, char *poststr)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	ssize_t n;
	snprintf(sendline, MAXSUB,
		 "%s %s %d %s\n", page, host, strlen(poststr), poststr);

	n = write(sockfd, sendline, strlen(sendline));


	/*
	   while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
	   recvline[n] = '\0';
	   printf("%s", recvline);
	   }
	 */
	return n;

}

int doclient(char *poststr, char *page)
{
	int sockfd;
	int n;
	struct sockaddr_in servaddr;

	char **pptr;
	//********** You can change. Puy any values here *******
	char *hname = "localhost";
	// char *page = "/chirico/test.php";
	//  char *poststr = "mode=login&user=test&password=test\r\n";
	//*******************************************************

	char str[50];
	struct hostent *hptr;
	if ((hptr = gethostbyname(hname)) == NULL) {
		syslog(LOG_ERR, " gethostbyname error for host: %s: %s",
		       hname, hstrerror(h_errno));
		return (1);
	}
	syslog(LOG_ERR, "hostname: %s\n", hptr->h_name);
	if (hptr->h_addrtype == AF_INET
	    && (pptr = hptr->h_addr_list) != NULL) {
		syslog(LOG_ERR, "address: %s\n",
		       inet_ntop(hptr->h_addrtype, *pptr, str,
				 sizeof(str)));
	} else {
		syslog(LOG_ERR, "Error call inet_ntop \n");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(10000);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	n = connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	//syslog(LOG_ERR, " n=connect=%d \n",n);
	process_http(sockfd, hname, page, poststr);
	close(sockfd);
	return (0);

}
