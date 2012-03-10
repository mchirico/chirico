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

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
extern int errno;

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include "version.h"



#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200
#define LISTENQ         1024
extern int h_errno;
int gflags = 0;
/* Do you really need this global? */
static char site[512];

static int verify_callback(int preverify_ok, X509_STORE_CTX * ctx)
{

	typedef struct {
		int verbose_mode;
		int verify_depth;
		int always_continue;
	} mydata_t;

	char buf[256];
	X509 *err_cert;
	int err, depth, mydata_index = 0;
	SSL *ssl;
	mydata_t *mydata;



	err_cert = X509_STORE_CTX_get_current_cert(ctx);
	depth = X509_STORE_CTX_get_error_depth(ctx);
	ssl =
	    X509_STORE_CTX_get_ex_data(ctx,
				       SSL_get_ex_data_X509_STORE_CTX_idx
				       ());
	err = X509_STORE_CTX_get_error(ctx);

#ifdef PDEBUG
	fprintf(stderr, "verify_callback err %i:%s\n", err,
		X509_verify_cert_error_string(err));
#endif

	mydata = SSL_get_ex_data(ssl, mydata_index);

	/*
	   X509_NAME_oneline(X509_get_issuer_name(ctx->current_cert), buf, 256);
	   or */
	X509_NAME_oneline(X509_get_subject_name(err_cert), buf, 256);

#ifdef PDEBUG
	printf("issuer= %s\n", buf);
#endif




	err = X509_STORE_CTX_get_error(ctx);

#ifdef PDEBUG
	fprintf(stderr, "X509_verify_cert_error_string=(%s)\n",
		X509_verify_cert_error_string(err));
#endif

	/* Return 1 accept the connection. 
	   Return 0 reject the connection 

	   This isn't the only place this decision is made to continue.

	 */

	preverify_ok = 1;
	return preverify_ok;
}


SSL_CTX *setup_client_ctx(void)
{
	SSL_CTX *ctx;
	ctx = SSL_CTX_new(SSLv23_method());
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2);
	return ctx;
}


ssize_t socket_write(int sockfd, char *_sendline)
{
	ssize_t n = 0;
	char sendline[MAXLINE + 1];
	snprintf(sendline, MAXLINE, _sendline);
	n = write(sockfd, sendline, strlen(sendline));
	return n;

}

ssize_t SSL_socket_write(SSL * ssl, char *_sendline)
{
	ssize_t n = 0;
	char sendline[MAXLINE + 1];
	snprintf(sendline, MAXLINE, _sendline);
	n = SSL_write(ssl, sendline, (int) strlen(sendline));
	return n;

}



char *socket_read(int sockfd, char *recvline)
{
	ssize_t n;

	n = read(sockfd, recvline, MAXLINE);
	recvline[n] = '\0';
	return recvline;
}

char *SSL_socket_read(SSL * ssl, char *recvline)
{
	ssize_t n;

	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	return recvline;
}


char *mygetopt(int argc, char **argv)
{
	static char s[2048];
	char email[512];
	char passwd[512];
	int c = 0;
	int flags = 0;

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
			printf("gauth -e <email> -p <password> -s <site>\n"
			       "Example:  ./gauth -e billybob -p Pa33word -s www.cwxstat.org\n");
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
			     "  svn checkout http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate gauth\n"
			     "Source:\n"
			     "  http://chirico.googlecode.com/svn/trunk/c/GoogleAuthenticate/src/gauth.c\n\n",
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
	if (~flags & 0x06) {
		fprintf(stderr, " -e <email> -p <password>\n");
		exit(2);
	}

	gflags = flags;
	snprintf(s, 1024,
		 "accountType=HOSTED_OR_GOOGLE&Email=%s&Passwd=%s&service=ah&\r\n",
		 email, passwd);
	return s;

}

/* This routine strips out the Auth token
 */
char *get_token(char *t)
{
	static char s[2048];
	char *p = 0;

	/* size_t len = strlen(t); */
	int i = 0;
	p = strstr(t, "Auth=");
	if (p == NULL) {
		s[0] = 0;
		return s;
	}
	while (*p != '\n' && *p != '\0' && *p != ' ' && i < 2048)
		s[i++] = *p++;
	s[i] = '\0';

	return s;

}

int write_token(char *t, const char *rcfile)
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




int main(int argc, char **argv)
{

	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
	int ret = 0;


	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);

	ctx = setup_client_ctx();


	/* Now doing standard connect stuff */

	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	char password[MAXLINE + 1];

	password[0] = '\0';
	sendline[0] = '\0';


	int sockfd;
	struct sockaddr_in servaddr;

	char **pptr;
	const char *hname = "www.google.com";

	/*Should this be listed here? */
	char poststr[1024];
	snprintf(poststr, 1024, "%s", mygetopt(argc, argv));



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

	servaddr.sin_port = htons(443);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	connect(sockfd, (SA *) & servaddr, sizeof(servaddr));


	sbio = BIO_new_socket(sockfd, BIO_NOCLOSE);
	ssl = SSL_new(ctx);
	SSL_set_bio(ssl, sbio, sbio);
	SSL_set_connect_state(ssl);


	/* Circuit Breaker - NO encrypted connection */
	if (SSL_do_handshake(ssl) == 1) {
#ifdef PDEBUG
		fprintf(stderr, "SSL_do_handshake(ssl)=%d\n", 1);
#endif
	} else {
		fprintf(stderr, "SSL handshake error= %d\n",
			SSL_get_error(ssl, ret));
		fprintf(stderr,
			"Cannot establish an encrypted connection\nExiting\n\n");
		return 1;
	}

	char header[8012];

	/*

	   http://dev.mchirico.org/_ah/login?continue=http://dev.mchirico.org/&auth=DQAA..
	 */




	snprintf(header, 8012, "POST /accounts/ClientLogin HTTP/1.0\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %ld\r\n\r\n%s", strlen(poststr),
		 poststr);


#ifdef PDEBUG
	fprintf(stderr, "\n\n%s\n\n", header);
#endif
	SSL_socket_write(ssl, header);

	char *s = get_token(SSL_socket_read(ssl, recvline));
	write_token(s, ".gauthrc");
	fprintf(stderr, "\n***********\n%s\n", s);





	SSL_shutdown(ssl);
	SSL_clear(ssl);

	fprintf(stderr, "SSL Connection closed\n");

	SSL_free(ssl);
	SSL_CTX_free(ctx);


	return 0;

}
