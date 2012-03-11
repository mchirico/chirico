/* Copyright GPL 2004 Mike Chiriico mmc mchirico@users.sourceforge.net
   Updated: Mon Jan  8 13:38:23 EST 2007




  





indent -kr -i8                                                         
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
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <getopt.h>
#include "wrapper.h"


#define SA      struct sockaddr	/* keeps the lines shorter. Note sockaddr and not sockaddr_in; it's generic */
#define MAXLINE 4096
/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ         1024	/* 2nd argument to listen() */
#define MAXSOCKADDR  128	/* max socket address structure size */
#define MAX_SQLSELECT 1000
#define RBUF_INCREMENT 1000
#define Q_BUF 1024
pthread_mutex_t mrx_mutex = PTHREAD_MUTEX_INITIALIZER;


FILE *fp;
int fd;
char username[20], password[20], database[20];
char qbuf[Q_BUF];
int count, num_fields, i;



/* connection testing */
pthread_mutex_t conn_mutex = PTHREAD_MUTEX_INITIALIZER;
#define CTBLMAX 12
struct conntbl {
	int conn;
	pthread_t t;
	int fd;
	int FLAG;
} conntbl[CTBLMAX];
int conn_count = -1;
/* for asyc_write */
struct S_Buf {
	int conn;
	char *s;
};



/* normally these would go in a header */
void process_stuff(int, int me);
int sockfd_to_family(int);


//Correct rawread
void rawfileread(int stockfd, int me)
{
	int n;
	int buf;


		while ((n = read(conntbl[me].fd, &buf, 1)) > 0) {
			write(stockfd, &buf, 1);
			fprintf(stderr,"%c",buf);
			buf = 0;

		}

	fprintf(stderr, "End of Rawread\n");
}

void rawfilereadlseek0(int stockfd, int me)
{
	int n;
	int buf;

	lseek(conntbl[me].fd,0,SEEK_SET);

		while ((n = read(conntbl[me].fd, &buf, 1)) > 0) {
			write(stockfd, &buf, 1);
			fprintf(stderr,"%c",buf);
			buf = 0;

		}

	fprintf(stderr, "End of Rawread\n");
}





static void *asyc_write(void *arg)
{
	int conn;
	char *s;

	conn = ((struct S_Buf *) arg)->conn;
	s = ((struct S_Buf *) arg)->s;

	/* fprintf(stderr, "asyc_write s.len=%d ->%s<-\n", strlen(s), s); */
	write(conn, s, strlen(s));

	free(s);
	free(arg);
	Pthread_detach(pthread_self());
	return (NULL);
}





void process_stuff(int sockfd, int me)
{
	ssize_t n;
	char line[MAXLINE + 1];
	char bbuf[MAXLINE + 50];
	int i;
	struct S_Buf *s_b;
	pthread_t t;

	sockfd_to_family(sockfd);
	while (1) {		/* there is a problem here that we may not read everything at once */
		if ((n = read(sockfd, line, MAXLINE)) <= 0) {
			fprintf(stderr,
				"*** ***** * return in process_stuff ... read == 0\n");
			pthread_t tmp = pthread_self();
			for (i = 0; i < CTBLMAX; ++i) {
				Pthread_mutex_lock(&conn_mutex);
				if (conntbl[i].t == tmp) {
					conntbl[i].FLAG = 0;
					conn_count--;
				}
				Pthread_mutex_unlock(&conn_mutex);
			}
			return;
		}

		if (line[n - 1] == '\n')
			fprintf(stderr, "it is a slash n\n");
		if (line[n - 1] == '\r')
			fprintf(stderr, "it is a slash r\n");
		if (n > 2)
			fprintf(stderr,
				"n=%d last[n-2]=%d last[n-1]=%d  last[n]=%d  ",
				(int) n, (int) line[n - 2],
				(int) line[n - 1], (int) line[n]);
		if (n == 2)
			fprintf(stderr, "n=%d last[n-1]=%d  last[n]=%d  ",
				(int) n, (int) line[n - 1], (int) line[n]);
		if (n == 1)
			fprintf(stderr, "n=%d  last[n]=%d  ", (int) n,
				(int) line[n]);
		/* sleep(1); */

		line[n] = '\0';
		fprintf(stderr, "client(%d) sent: bytes(%d)", (int) me,
			(int) n);
		if (strncmp(line, "READFILE|", 9) == 0) {
			fprintf(stderr, " Starting readfile\n");
			rawfileread(sockfd, me);
		} else if (strncmp(line, "RESET|", 5) == 0) {
			fprintf(stderr, " lseek 0 readfile\n");
			rawfilereadlseek0(sockfd, me);
		} else if (strncmp(line, "ECHO|", 5) == 0) {
			fprintf(stderr, "Starting echo\n");
			snprintf(bbuf, MAXLINE + 50, "%s:SERVER ECHO: ",
				 line);
			write(sockfd, bbuf, strlen(bbuf));
		} else if (strncmp(line, "STAT|", 5) == 0) {
			for (i = 0; i < CTBLMAX; ++i) {
				Pthread_mutex_lock(&conn_mutex);
				if (conntbl[i].FLAG == 1) {
					snprintf(bbuf, MAXLINE, "%d ", i);
					write(sockfd, bbuf, strlen(bbuf));
				}
				Pthread_mutex_unlock(&conn_mutex);
			}



			fprintf(stderr, "Starting STAT\n");
			snprintf(bbuf, MAXLINE, "Connections: %d",
				 conn_count);
			write(sockfd, bbuf, strlen(bbuf));
		} else if (strncmp(line, "WRITE|", 5) == 0) {

			fprintf(stderr, "Starting WRITE\n");
			snprintf(bbuf, MAXLINE, "%s ", line);
			s_b =
			    (struct S_Buf *) malloc(sizeof(struct S_Buf));
			s_b->s =
			    (char *) malloc(sizeof(char) * sizeof(bbuf));
			strcpy(s_b->s, bbuf);

			/* At this point only setup for checking.
			   This works with (0-4) connections.
			 */
			if (line[6] == '0' && conntbl[0].FLAG != 0) {	/* make sure you change these numbers */
				s_b->conn = conntbl[0].conn;
				Pthread_create(&t, NULL, &asyc_write, s_b);
			}
			if (line[6] == '1' && conntbl[1].FLAG != 0) {
				s_b->conn = conntbl[1].conn;
				Pthread_create(&t, NULL, &asyc_write, s_b);
			}
			if (line[6] == '2' && conntbl[2].FLAG != 0) {
				s_b->conn = conntbl[2].conn;
				Pthread_create(&t, NULL, &asyc_write, s_b);
			}
			if (line[6] == '3' && conntbl[3].FLAG != 0) {
				s_b->conn = conntbl[3].conn;
				Pthread_create(&t, NULL, &asyc_write, s_b);
			}
			if (line[6] == '4' && conntbl[4].FLAG != 0) {
				s_b->conn = conntbl[4].conn;
				Pthread_create(&t, NULL, &asyc_write, s_b);
			}


		} else {
			write(sockfd, "HELLO FR SERVER: ", strlen("HELLO FR SERVER: "));	/* the test client will block on read  */
		}		/* Also Microsoft will terminate on Null */


	}
}


int sockfd_to_family(int sockfd)
{
	struct sockaddr_in sa;
	socklen_t len;
	len = sizeof(sa);
	if (getpeername(sockfd, (struct sockaddr *) &sa, &len) < 0)
		return -1;
	fprintf(stderr, "client: %s: %d\n", inet_ntoa(sa.sin_addr),
		(int) ntohs(sa.sin_port));
	return (sa.sin_port);
}




static void *do_init(void *arg)
{
	int connfd;
	int me;



	connfd = *((int *) arg);
	free(arg);


	Pthread_mutex_lock(&conn_mutex);
	conn_count++;
	conntbl[conn_count].conn = connfd;
	conntbl[conn_count].t = pthread_self();
	if ((conntbl[conn_count].fd =
	     open("./tmpfile", O_RDONLY, 0600)) == -1) {
		fprintf(stderr, "Can't open file (%s): %s\n", "tmpfile",
			strerror(errno));
		conntbl[conn_count].fd = -1;
	} 

	conntbl[conn_count].FLAG = 1;
	me = conn_count;
	Pthread_mutex_unlock(&conn_mutex);



	/* needs to be called in thread handler */

	pthread_detach(pthread_self());
	process_stuff(connfd, me);
	close(connfd);
	return (NULL);
}




int main(int argc, char **argv)
{


	int flags = 0, c = 0;
	char File_Location[1024];

	while (1) {

		int option_index = 0;
		static struct option long_options[] = {
			{"help", 0, 0, 'h'},
			{"location", 1, 0, 'l'},
			{"daemon", 0, 0, 'd'},
			{"version", 0, 0, 'v'},
			{"sector", 0, 0, 's'},
			{0, 0, 0, 0}
		};

		c = getopt_long(argc, argv, "hl:dvs",
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
			printf(" -h help\n");
			printf(" -f follow. Like tail -f\n");
			printf
			    (" -l location of file. Defaults to ./weatherbinary\n");
			return 0;
			break;

		case 'l':
			flags |= 0x2;
			snprintf(File_Location, 1024, "%s", optarg);
			break;

		case 'd':
			flags |= 0x04;
			break;

		case 'v':
			flags |= 0x8;
			printf("option v\n");
			break;

		case 's':
			flags |= 0x10;
			printf("option s\n");
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



	if ((0x04 & flags) == 0x04) {
		// Go into daemon mode
		daemon(1, 0);
	}









	int listenfd, *connfdptr;
	socklen_t clilen;
	pthread_t t;
	struct sockaddr_in cliaddr, servaddr;
	printf("weblite version 0.0.1\n");




	int i;
	for (i = 0; i < CTBLMAX; ++i) {
		conntbl[i].conn = 0;
		conntbl[i].t = 0;
		conntbl[i].FLAG = 0;
	}


	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(10000);
	bind(listenfd, (SA *) & servaddr, sizeof(servaddr));
	listen(listenfd, LISTENQ);




	while (1) {
		clilen = sizeof(cliaddr);
		connfdptr = (int *) malloc(sizeof(int));	/* free is called in do_init */
		*connfdptr = accept(listenfd, (SA *) & cliaddr, &clilen);
		Pthread_create(&t, NULL, &do_init, connfdptr);
		fprintf(stderr, "Creating a connection\n");
	}

}
