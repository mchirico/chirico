/*  Copyright (C) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>
    Version: 0.0.6
    Updated: Mon Mar  6 08:08:11 EST 2006

     Example usage:

          ./stock <ticker symbol>
     or
          ./stock AAPL
            "AAPL",30.40,"7/8/2004","10:41am",+0.01,30.13,30.50,29.95,908979

     To get all stock in DJI

        ./stock "^DJI,AA,GE,JNJ,MSFT,AXP,GM,JPM,PG,BA,HD,KO,SBC,C,HON,MCD,T,CAT,HP,MMM,UTX,DD,IBM,MO,WMT,DIS,INTC,MRK,XOM,EK,IP"


     Reference:
      http://souptonuts.sourceforge.net/chirico/test.php
      http://souptonuts.sourceforge.net/code/test.php.html

     Download:
      http://ftp1.sourceforge.net/souptonuts/stock.tar.gz

     CVS:
      http://cvs.sourceforge.net/viewcvs.py/cpearls/cpearls/src/posted_on_sf/stock/

*/


/*  stockhistory

    Copyright GPL 2003 by Mike Chirico <mchirico@users.sourceforge.net>
    Updated: Thu Jul  8 10:55:25 EDT 2004

     Example usage:

          ./stockhistory <ticker symbol>
     or
          ./stockhistory AAPL
            "AAPL",30.40,"7/8/2004","10:41am",+0.01,30.13,30.50,29.95,908979
            ... lots of data going back since 1930




     Reference:
      http://souptonuts.sourceforge.net/chirico/test.php
      http://souptonuts.sourceforge.net/code/test.php.html

     Download:
      http://prdownloads.sourceforge.net/cpearls/spider.tar.gz?download

*/

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>


#define SA      struct sockaddr
#define MAXLINE 16384
#define READMAX 16384		//must be less than MAXLINE or equal
#define NUM_BLK 20
#define MAXSUB  512
#define URL_LEN 256
#define I_LEN   256
#define STARTYR   2003
#define ENDYR   2004
#define ICHK   20



#define LISTENQ         1024

extern int h_errno;



int Socket(int family, int type, int protocol)
{
	int n;
	if ((n = socket(family, type, protocol)) < 0)
		fprintf(stderr, "socket error: socket(%d,%d,%d)\n", family,
			type, protocol);
	return (n);
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		fprintf(stderr, "connect error:\n");

}

void Close(int fp)
{
	int error;
	// Restart close should a signal occur */
	while (((error = close(fp)) == -1) && (errno == EINTR));
	if (error == -1)
		fprintf(stderr,
			"Failed to close the file in close statement\n");


}




ssize_t process_http_get(int sockfd, char *host, char *page, char *ichk)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1],
	    buf[NUM_BLK * MAXLINE + 1];
	ssize_t n;
	unsigned int i, buflen, ichklen, k = 0;
	int flag = 0;

	snprintf(sendline, MAXSUB, "GET %s HTTP/1.0\r\n"
		 /*  "Connection: Keep-Alive\r\n" */
		 "Pragma: no-cache\r\n"
		 "Host: %s\r\n"
		 "Accept: www/source\r\n"
		 "Accept: application/octet-stream\r\n"
		 "Accept: text/html\r\n\r\n", page, host);


	write(sockfd, sendline, strlen(sendline));
	buf[0] = '\0';
	while ((n = read(sockfd, recvline, READMAX)) > 0) {
		recvline[n] = '\0';
		//fprintf(stderr,"n=%d\n",n);
		if ((strlen(buf) + n) < (NUM_BLK * MAXLINE))
			strncat(buf, recvline, MAXLINE);

	}


	buflen = strlen(buf);
	ichklen = strlen(ichk);
	buflen = buflen - 5;


	for (i = 0; i < buflen && flag >= 0; ++i) {
		if (buf[i] == '\r' && buf[i + 1] == '\n'
		    && buf[i + 2] == '\r' && buf[i + 3] == '\n') {
			flag = i;
		}

		if (buf[i] == '\n') {
			k = 0;

			while ((buf[i + k + 1] == ichk[k])
			       && (k < ichklen)) {
				if (++k == ichklen) {
					printf("%s", &buf[i + 1]);
					flag = -1;
				}

			}
		}

	}

	if ((n = strlen(buf)) > 85) {
		char *c;
		c = strstr(&buf[n - 85], "finance.dcn.yahoo.com");
		if (c != NULL) {
			flag = -1;

		} else {
			flag = 0;
		}
	}

	return flag;

}

int Getopt (int argc, char **argv, char ibuf[])
{

	int flags = 0, c;
        


	while ((c = getopt(argc, argv, "vhsiH")) != -1) {
		switch (c) {
		case 'v':
			flags |= 0x1;
			fprintf(stderr,
				"Copyright (C) GPL 2006 by Mike Chirico\n<mchirico@users.sourceforge.net>\n");
			fprintf(stderr, "version 0.0.6\n\n");
			fprintf(stderr,
				"download: http://ftp1.sourceforge.net/souptonuts/stock.tar.gz\n");
			exit(0);
			break;
		case 'h':
			flags |= 0x2;
			fprintf(stderr,
				"Copyright (C) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>\n");
			fprintf(stderr,
				"\nUsage: stock <Nasdaq Ticker|[,Tickers]>\n"
				" Tickers are case insensitive\n\n"
				"  $ stock rhat\n or\n"
				"  $ stock \"^DJI,AA,GE,JNJ,MSFT,AXP,GM,JPM,\\\n"
				"PG,BA,HD,KO,SBC,C,HON,MCD,T,CAT,HP,MMM,UTX,DD,IBM,MO,WMT,DIS,INTC,MRK,XOM,EK,IP\"\n\n");
		        fprintf(stderr,
			   "stock -H will give daily stock prices since 1930\n"
			  "\nUsage: stock -H <Nasdaq Ticker>  \"<date>\"\n\n"
			"  $ stock -H AAPL  \"dd-mm\"\n"
                        "    or \n"
                        "  $ ./stock -H AAPL `date '+%s-%s'`\n\n"
			" Yahoo will sometimes skip a few days. <date> is the check \n"
			,"%d","%b");
			exit(0);
			break;
		case 's':	// Sector
			flags |= 0x3;
			break;
		case 'i':	// Industry
			flags |= 0x4;
			break;
		case 'H':	// History
			flags |= 0x5;
			break;
		case '?':
			flags |= 0x10;
			fprintf(stderr, "Unrecognized option  \n");
			exit(1);
			break;
		}
	}








}


int main(int argc, char **argv)
{

  int flags=0;
  char ibuf[I_LEN + 1];

  flags=Getopt(argc,argv,ibuf);


	if (argc < 2) {

		exit(1);
	}


	int sockfd;
	struct sockaddr_in servaddr;
	int n;
	char **pptr;
	char ichk[ICHK + 1];

	if (argc < 3) {
		fprintf(stderr,
			"\n\nQualifying Date could be used:  <dd-month>\n   ./stockhistory AAPL \"8-Jul\"\n\n\n");
		exit(1);
	} else {
		snprintf(ichk, ICHK, "%s", argv[2]);
	}




	//********** You can change. Put any values here *******

	char month[3], day[3], year[5];
	struct timeval tv;

	time_t curtime;


	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec;

	strftime(month, 3, "%m", localtime(&curtime));
	strftime(day, 3, "%d", localtime(&curtime));
	strftime(year, 5, "%Y", localtime(&curtime));
	//fprintf(stderr, " %s-%s-%s\n", month, day, year);

	char *hname = "ichart.finance.yahoo.com";
	char page[URL_LEN + 1];

	snprintf(page, URL_LEN,
		 "/table.csv?s=%s&a=00&b=2&c=%d&d=%d&e=%s&f=%s&g=d&ignore=.csv",
		 argv[1], STARTYR, atoi(month) - 1, day, year);


	/*
	   The following  6/2/2004 to 6/11/2004

                                                                           v----v-----v------------- 9/17/2004
        http://ichart.finance.yahoo.com/table.csv?s=AAPL&a=00&b=2&c=2003&d=9&e=17&f=04&g=d&ignore=.csv
                                                           ^----^---^---  0/2/2003   from



	 */



	char str[50];
	struct hostent *hptr;
	if ((hptr = gethostbyname(hname)) == NULL) {
		fprintf(stderr, " gethostbyname error for host: %s: %s",
			hname, hstrerror(h_errno));
		exit(1);
	}
	//printf("hostname: %s\n", hptr->h_name);
	if (hptr->h_addrtype == AF_INET
	    && (pptr = hptr->h_addr_list) != NULL) {

		inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
	} else {
		fprintf(stderr, "Error call inet_ntop \n");
	}

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(80);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	Connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	fprintf(stderr, "%s%s", hname, page);
	n = process_http_get(sockfd, hname, page, ichk);
	Close(sockfd);

	if (n < 0)
		return 0;
	else {
		fprintf(stderr, "./stockhistory %s ${startdate}>%s\n",
			argv[1], argv[1]);
		return 1;
	}



}
