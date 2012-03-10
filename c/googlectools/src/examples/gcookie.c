/*  
# Copyright 2008 Mike Chirico mchirico@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
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
#include <getopt.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
extern int errno;


#define SA      struct sockaddr
#define MAXLINE 8012
#define MAXSUB  MAXLINE - 1024
#define BUFMAX  1024


#define LISTENQ         1024

extern int h_errno;
static char site[1024];
int gflags = 0;

char *parse_cookie(char *);


ssize_t process_http(int sockfd, char *host, char *page, char *poststr)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	static char rtpg[MAXLINE];
	ssize_t n, i = MAXLINE;

	snprintf(sendline, MAXSUB,
		 "POST %s HTTP/1.0\r\n"
		 "Host: %s\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %ld\r\n\r\n"
		 "%s", page, host, strlen(poststr), poststr);

	/*      printf("%s\n",sendline); */
	write(sockfd, sendline, strlen(sendline));
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = '\0';
		strncat(rtpg, recvline, (size_t) i);
		i = i - n;
		if (i < 0)
			i = 0;
	}
	write_cookie(parse_cookie(rtpg), ".gcookierc");
	return n;

}



char *read_auth()
{
	static char buf[BUFMAX];
	static char s[MAXLINE];
	char *p = 0;
	int fd = 0;
	size_t j = MAXLINE;
	ssize_t n = 0;

	s[0] = '\0';


	if ((fd = open(".gauthrc", O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "write_token error in file open: %s\n",
			strerror(errno));
		return s;
	}
	while ((n = read(fd, buf, BUFMAX)) > 0) {
		buf[n] = '\0';
		strncat(s, buf, j);
		j = j - (size_t) n;
	}

	p = s;
	while (*p++) {
		if (*p == '\n') {
			*p = '\0';
		}
	}
	if (strstr(s, "Auth=") != NULL)
		return &s[5];
	else {
		s[0] = '\0';
		return s;
	}
}



/*
Set-Cookie: ACSID=
 */

char *parse_cookie(char *t)
{
	static char s[MAXLINE];
	char *p = 0;
	char *tp = 0;

	s[0] = '\0';;
	p = strstr(t, "Set-Cookie: ACSID=");
	if (p != NULL) {
		tp = p;
		while (*tp) {
			if (*tp == '\n') {
				*tp = '\0';
				break;
			}
			tp++;
		}
		snprintf(s, MAXLINE, "%s", p);
	}



	return s;

}

int write_cookie(char *t, char *rcfile)
{
	int fd;


	if ((fd = open(rcfile, O_RDWR | O_CREAT, 0600)) == -1) {
		fprintf(stderr, "write_token error in file open: %s\n",
			strerror(errno));
		return 1;
	}
	write(fd, t, strlen(t));
	write(fd, "\n", 1);
	close(fd);
	return 0;


}




char *mygetopt(int argc, char **argv)
{
	static char s[2048];
	char email[512];
	char passwd[512];
	int c = 0;
	int flags = 0;

	s[0] = 0;
	site[0] = 0;

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", 0, 0, 'h'},
			{"email", 1, 0, 'e'},
			{"password", 1, 0, 'p'},
			{"version", 0, 0, 'v'},
			{"site", 1, 0, 's'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "he:p:vs:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			printf("option %s",
			       long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;

		case 'h':
			flags |= 0x1;
			printf
			    ("gcookie -s <site>\n"
			     "Example:  ./gcookie -s www.cwxstat.org\n");
			exit(0);
			break;

		case 'e':
			flags |= 0x2;
			printf("option c with value `%s'\n", optarg);
			snprintf(email, 512, "%s", optarg);
			break;

		case 'p':
			flags |= 0x4;
			printf("option c with value `%s'\n", optarg);
			snprintf(passwd, 512, "%s", optarg);
			break;

		case 'v':
			flags |= 0x8;
			printf
			    ("Copyright (C) GPL 2008 by Mike Chirico <mchirico@gmail.com>\n"
			     "version %s \n" "  try --help\n" "Download:\n"
			     "  <need to fill in>\n" "Subversion:\n"
			     "  svn checkout http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate glogin\n"
			     "Source:\n"
			     "  http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate/src/glogin.c\n\n",
			     VERSION);

			exit(0);
			break;

		case 's':
			flags |= 0x10;
			snprintf(site, 512, "%s", optarg);
			break;


		case '?':
			break;

		default:
			printf
			    ("?? getopt returned character code 0%o ??\n",
			     c);
		}
	}

	if (optind < argc) {
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}
	printf("argc=%d\n", argc);
	if (flags & 0x1) {
		printf("h flag\n");
	}
	if (~flags & 0x10) {
		fprintf(stderr, " -s <site>\n");
		exit(2);
	}

	gflags = flags;
	/* Clean up lengths */
	snprintf(s, 512, "%s", site);

	return s;

}






int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	static char s[MAXLINE];
	static char hname[MAXLINE];
	static char page[MAXLINE];
	static char auth[MAXLINE];

	snprintf(auth, MAXLINE, "%s", read_auth());
	fprintf(stderr, "\n\n%s\n\n", auth);

	mygetopt(argc, argv);


	char **pptr;
	//********** You can change. Puy any values here *******
	snprintf(hname, MAXLINE, "%s", site);
	fprintf(stderr, "hname=%s\n", hname);
	snprintf(page, MAXLINE, "/_ah/login?continue=http://%s&auth=%s&",
		 site, auth);
	/*      char *poststr = "action=ActionToDo&hash=3ad540e4c39f54d0d138c60d66c1d923&\r\n";  */
	char *poststr = s;
	fprintf(stderr, "poststr=%s\n", poststr);
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
