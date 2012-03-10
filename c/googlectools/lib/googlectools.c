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
#include "googlectools.h"
#include "_googlectools.h"

int test()
{
	fprintf(stderr, "this is a test\n");
	return 0;
}

#include "version.h"



#define SA      struct sockaddr
#define MAXLINE 8192
#define MAXBUF  1024
#define MAXSUB  200
#define LISTENQ 1024
extern int h_errno;


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



char *gauth(const char *email, const char *passwd, const char *service)
{
	static char auth[MAXLINE];
	auth[0] = '\0';

	if (strlen(email) <= 0)
		return NULL;
	if (strlen(passwd) <= 0)
		return NULL;

	return _gauth(email, passwd, auth, service);
}

/* Break this out into general routines:
   1. Build poststr
   2. Build header

  This way you can get rid of duplicate code
*/
static char *_build_header()
{

  return NULL;
}








static char *_gauth(const char *email, const char *passwd, char *auth, const char *service)
{
	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
	int ret = 0;

	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);

	ctx = setup_client_ctx();

	char sendline[MAXLINE], recvline[MAXLINE], password[MAXLINE],
	    header[MAXLINE];
	sendline[0] = '\0', recvline[0] = '\0', password[0] =
	    '\0', header[0] = '\0';

	int sockfd;
	struct sockaddr_in servaddr;

	char **pptr;
	const char *hname = "www.google.com";

	char poststr[MAXLINE];

	/*
	  Service:
             (Reference: http://code.google.com/support/bin/answer.py?answer=62712&topic=10711)
	  ah = appengine
	  cl = calendar
	 */

	snprintf(poststr, MAXLINE,
		 "accountType=HOSTED_OR_GOOGLE&Email=%s&Passwd=%s&service=%s&\r\n",
		 email, passwd, service);

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
		return NULL;
	}

	snprintf(header, 8012, "POST /accounts/ClientLogin HTTP/1.0\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %zd\r\n\r\n%s", strlen(poststr),
		 poststr);

#ifdef PDEBUG
	fprintf(stderr, "\n\n%s\n\n", header);
#endif
	SSL_socket_write(ssl, header);


	snprintf(auth, MAXLINE, "%s",
		 get_token(SSL_socket_read(ssl, recvline)));

	SSL_shutdown(ssl);
	SSL_clear(ssl);

	SSL_free(ssl);
	SSL_CTX_free(ctx);

	return auth;

}


static char *cleanup_token(const char *t, const char *tag)
{
	static char s[MAXLINE];
	char *p = 0;
	char *tp = 0;
	size_t len = 0;

	s[0] = '\0';

	len = strlen(tag);
	if (len == 0)
		return NULL;

	p = strstr(t, tag);
	if (p == 0)
		return NULL;
	p += len;
	tp = strstr(t, ";");
	if (tp != NULL)
		*tp = '\0';
	snprintf(s,MAXLINE, "%s", p);
	return s;
}


char *gxauth(const char *auth)
{

	if (strlen(auth) <= 0)
		return NULL;
	return _gxauth(auth);
}

static char *_gxauth(const char *auth)
{
	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
	int ret = 0;
	char *p = 0;
	p = cleanup_token(auth, "Auth=");

	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);
	ctx = setup_client_ctx();
	char sendline[MAXLINE], recvline[MAXLINE], password[MAXLINE],
	    header[MAXLINE];
	sendline[0] = '\0', recvline[0] = '\0', password[0] =
	    '\0', header[0] = '\0';
	int sockfd;
	struct sockaddr_in servaddr;
	char **pptr;
	const char *hname = "www.google.com";
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
		return NULL;
	}

	snprintf(header, 8012,
		 "GET /accounts/AuthSubRevokeToken HTTP/1.1\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Authorization: AuthSub Auth=\"%s\"\r\n" 
		 "User-Agent: Java/1.5.0_06\r\n"
		 "Host: https://www.google.com\r\n"
		 "Accept: text/html, image/gif, image/jpeg, *; q=.2, */*; q=.2\r\n"
                 "Connection: keep-alive\r\n\r\n", p);




#ifdef PDEBUG
	fprintf(stderr, "\n\n%s\n\n", header);
#endif
	SSL_socket_write(ssl, header);
	SSL_socket_read(ssl, recvline);
	fprintf(stderr,"%s\n\n",recvline);

	SSL_shutdown(ssl);
	SSL_clear(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return NULL;
}


char *giauth(const char *auth)
{

	if (strlen(auth) <= 0)
		return NULL;
	return _giauth(auth);
}

static char *_giauth(const char *auth)
{
	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
	int ret = 0;
	char *p = 0;
	p = cleanup_token(auth, "Auth=");

	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);
	ctx = setup_client_ctx();
	char sendline[MAXLINE], recvline[MAXLINE], password[MAXLINE],
	    header[MAXLINE];
	sendline[0] = '\0', recvline[0] = '\0', password[0] =
	    '\0', header[0] = '\0';
	int sockfd;
	struct sockaddr_in servaddr;
	char **pptr;
	const char *hname = "www.google.com";
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
		return NULL;
	}

	snprintf(header, 8012,
		 "GET /accounts/AuthSubTokenInfo HTTP/1.1\r\n"
		 "Content-Type: application/x-www-form-urlencoded\r\n"
		 "Authorization: AuthSub token=\"%s\"\r\n" 
		 "User-Agent: Java/1.5.0_06\r\n"
		 "Host: https://www.google.com\r\n"
		 "Accept: text/html, image/gif, image/jpeg, *; q=.2, */*; q=.2\r\n"
                 "Connection: keep-alive\r\n\r\n", p);

#ifdef PDEBUG
	fprintf(stderr, "\n\n%s\n\n", header);
#endif
	SSL_socket_write(ssl, header);
	SSL_socket_read(ssl, recvline);
	fprintf(stderr,"%s\n\n",recvline);

	SSL_shutdown(ssl);
	SSL_clear(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return NULL;
}


char *gspread(const char *auth)
{
	if (strlen(auth) <= 0)
		return NULL;
	return _gspread(auth);

}

  /*
   *    http://code.google.com/apis/spreadsheets/developers_guide_protocol.html#createSpreadsheet
   *   (Great Ruby tutorial:
   *        http://code.google.com/support/bin/answer.py?answer=93164&useful=1&show_useful=1)
   */
static char *_gspread(const char *auth)
{
  
  if (auth != NULL)
  return NULL;

  return NULL;


}





char *gcal(const char *auth)
{

	if (strlen(auth) <= 0)
		return NULL;
	return _gcal(auth);
}


static char *_gcal(const char *auth)
{
  return NULL;

}








/* 
      The secure method needs a signed request.
      Reference: http://code.google.com/apis/accounts/docs/AuthForWebApps.html#signingrequests
   
 */
/* Commented out */
#if 0

static char *_gcal(const char *auth)
{
	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
	int ret = 0;
	char *p = 0;
	p = cleanup_token(auth, "Auth=");

	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);
	ctx = setup_client_ctx();
	char sendline[MAXLINE], recvline[MAXLINE], password[MAXLINE],
	    header[MAXLINE];
	sendline[0] = '\0', recvline[0] = '\0', password[0] =
	    '\0', header[0] = '\0';
	int sockfd;
	struct sockaddr_in servaddr;
	char **pptr;
	const char *hname = "www.google.com";
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
		return NULL;
	}

	snprintf(header, 8012,
		 "GET /calendar/feeds/default/private/full HTTP/1.1\r\n"
		 "Content-Type: application/x-www-form-urlencoded\r\n"
		 "Authorization: AuthSub token=\"%s\"\r\n" 
		 "User-Agent: Java/1.5.0_06\r\n"
		 "Host: www.google.com\r\n"
		 "Accept: text/html, image/gif, image/jpeg, *; q=.2, */*; q=.2\r\n"
                 "Connection: keep-alive\r\n\r\n", p);

#ifdef PDEBUG
	fprintf(stderr, "\n\n%s\n\n", header);
#endif
	SSL_socket_write(ssl, header);
	SSL_socket_read(ssl, recvline);
	fprintf(stderr,"%s\n\n",recvline);

	SSL_shutdown(ssl);
	SSL_clear(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return NULL;
}

#endif









char *gcookie(char *auth, const char *_site)
{
	static char _cookie[MAXLINE];
	_cookie[0] = '\0';
	if (strlen(auth) <= 0)
		return NULL;
	if (strlen(_site) <= 0)
		return NULL;
	return _gcookie(auth, _site);
}


static char *_gcookie(char *_auth, const char *_site)
{

	int sockfd;
	struct sockaddr_in servaddr;
	static char hname[MAXLINE];
	static char page[MAXLINE];
	static char auth[MAXLINE];
	static char poststr[MAXLINE];
	char *p;
	char *e;
	p = strstr(_auth, "=");
	e = strstr(_auth, "\n");
	if (e != NULL) {
		e++;
		*e = '\0';
	}

	if (p != NULL)
		++p;		/* = sign */
	if (p == NULL) {
		p = _auth;
	}

	snprintf(auth, MAXLINE, "%s", p);
	snprintf(hname, MAXLINE, "%s", _site);
	snprintf(page, MAXLINE,
		 "/_ah/login?continue=http://%s&auth=%s&", _site, auth);
	/* Remove this */
	snprintf(poststr, MAXLINE, "%s", "test=a&");
	char **pptr;
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
	p = process_http(sockfd, hname, page, poststr);
	close(sockfd);
	/*      fprintf(stderr,"Before last return %s\n",p); */
	return p;
}


/* Expire Cookie */
char *gxcookie(char *auth, const char *_site)
{
	static char _cookie[MAXLINE];
	_cookie[0] = '\0';
	if (strlen(auth) <= 0)
		return NULL;
	if (strlen(_site) <= 0)
		return NULL;
	return _gxcookie(auth, _site);
}


static char *_gxcookie(char *_auth, const char *_site)
{

	int sockfd;
	struct sockaddr_in servaddr;
	static char hname[MAXLINE];
	static char page[MAXLINE];
	static char auth[MAXLINE];
	static char poststr[MAXLINE];
	char *p;
	char *e;
	p = strstr(_auth, "=");
	e = strstr(_auth, "\n");
	if (e != NULL) {
		e++;
		*e = '\0';
	}

	if (p != NULL)
		++p;		/* = sign */
	if (p == NULL) {
		p = _auth;
	}

	snprintf(auth, MAXLINE, "%s", p);
	snprintf(hname, MAXLINE, "%s", _site);
	snprintf(page, MAXLINE,
		 "/_ah/logout?continue=http://%s&auth=%s&", _site, auth);
	snprintf(poststr, MAXLINE, "%s", "test=a&");
	char **pptr;
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
	p = process_http(sockfd, hname, page, poststr);
	close(sockfd);
	return p;
}


char *post(char *hname, char *page, char *cookie, char *poststr)
{
	if (strlen(hname) <= 0) {
		fprintf(stderr, "post: hname is zero length\n");
		return NULL;
	}
	if (strlen(page) <= 0) {
		fprintf(stderr, "post: page is zero length\n");
		return NULL;
	}

	return _post(hname, page, cookie, poststr);
}

static char *_post(char *hname, char *page, char *cookie, char *poststr)
{

	int sockfd;
	struct sockaddr_in servaddr;
	char *p;
	char **pptr;
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
	p = process_post(sockfd, cookie, hname, page, poststr);
	close(sockfd);
	/*      fprintf(stderr,"Before last return %s\n",p); */
	return p;
}


char *parse_cookie(char *cookie)
{
	static char s[MAXLINE];
	char *p = 0;
	char *tp = 0;
	if (strlen(cookie) <= 0)
		return NULL;
	snprintf(s, MAXLINE, "%s", cookie);
	p = strstr(s, "Set-Cookie: ");
	if (p == NULL)
		return NULL;
	tp = strstr(s, "; ");
	if (tp != NULL) {
		tp++;
		*tp = '\0';
	}

	p += 12;
	return p;
}


static char *raw_http(int sockfd,const char *rawdata)
{
	char buf[MAXBUF];
	static char recvline[MAXLINE];
	ssize_t n = 0, j = 0;
	buf[0] = '\0';

	write(sockfd, rawdata, strlen(rawdata));
	while ((n = read(sockfd, buf, MAXBUF)) > 0) {
		buf[n] = '\0';
		j += n;
		if (j < MAXLINE) {
			strcat(recvline, buf);
		}
	}
	return recvline;
}




static char *process_post(int sockfd, char *cookie, char *host,
			  char *page, char *poststr)
{

	char sendline[MAXLINE];
	char buf[MAXBUF];
	static char recvline[MAXLINE];
	ssize_t n = 0, j = 0;
	buf[0] = '\0';
	snprintf(sendline, MAXLINE,
		 "POST %s HTTP/1.0\r\n"
		 "Cookie: $Version=\"1\"; %s\r\n"
		 "Host: %s\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %zd\r\n\r\n"
		 "%s", page, cookie, host, strlen(poststr), poststr);
	write(sockfd, sendline, strlen(sendline));
	while ((n = read(sockfd, buf, MAXBUF)) > 0) {
		buf[n] = '\0';
		j += n;
		if (j < MAXLINE) {
			strcat(recvline, buf);
		}
	}
	return recvline;
}




static char *process_http(int sockfd, char *host, char *page,
			  char *poststr)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	static char rtpg[MAXLINE];
	ssize_t n, i = MAXLINE;
	rtpg[0] = '\0';
	snprintf(sendline, MAXLINE,
		 "POST %s HTTP/1.0\r\n"
		 "Host: %s\r\n"
		 "Content-type: application/x-www-form-urlencoded\r\n"
		 "Content-length: %zd\r\n\r\n"
		 "%s", page, host, strlen(poststr), poststr);
	/* printf("sendline: %s\n", sendline); */
	write(sockfd, sendline, strlen(sendline));
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = '\0';
		strncat(rtpg, recvline, (size_t) i);
		i = i - n;
		if (i < 0)
			i = 0;
	}

	/* write_cookie(parse_cookie_file(rtpg), ".gcookierc"); */
	return rtpg;
}


static char *parse_cookie_file(char *t)
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

int write_cookie(char *t, const char *rcfile)
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
