/*  Copyright (C) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>



  If you're using postfix,  in the file /etc/postfix/main.cf
  make the following changes:

         smtpd_tls_loglevel = 2

  When this client connect to your postfix server, you'll
  want to see if there are any problems.

  Don't forget to restart postfix.



Similiar Products:

  POPFile
   http://popfile.sourceforge.net/



Notes:


      BIO_new_socket:
         sbio=BIO_new_socket(s,BIO_NOCLOSE);



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

     VERP
        http://cr.yp.to/proto/verp.txt



You must encode the password using Base64. This is put in the
file password_smtp_64 with no return after the encoded login username.

perl -MMIME::Base64 -e     'print encode_base64("\000mchirico\@linuxaddicted.org\000password");' > password_smtp_64


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
#include <fcntl.h>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>




#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200
#define LISTENQ         1024
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
	int err, depth, mydata_index=0;
	SSL *ssl;
	mydata_t *mydata;



	err_cert = X509_STORE_CTX_get_current_cert(ctx);
	depth = X509_STORE_CTX_get_error_depth(ctx);
	ssl =
	    X509_STORE_CTX_get_ex_data(ctx,
				       SSL_get_ex_data_X509_STORE_CTX_idx
				       ());
	err = X509_STORE_CTX_get_error(ctx);
	fprintf(stderr, "  err %i:%s\n", err,
		X509_verify_cert_error_string(err));

	mydata = SSL_get_ex_data(ssl, mydata_index);

	/*
	   X509_NAME_oneline(X509_get_issuer_name(ctx->current_cert), buf, 256);
	   or */
	X509_NAME_oneline(X509_get_subject_name(err_cert), buf, 256);
	printf("issuer= %s\n", buf);




	err = X509_STORE_CTX_get_error(ctx);
	fprintf(stderr, "X509_verify_cert_error_string=(%s)\n",
		X509_verify_cert_error_string(err));

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


int get_password(char *file, char *password, int length)
{
  FILE *fp;
  char * line = NULL;
  ssize_t read;
  size_t  len;
  fp = fopen(file,"r");
  if (fp == NULL) {
    fprintf(stderr,"Can't read password file\n");
    return 0;
  }
  len = (size_t) length;
  read = getline(&line, &len, fp);

  snprintf(password,MAXLINE,"%s",line);


  if(strlen(password) > 0)
  if(password[strlen(password)-1] == '\n')
    password[strlen(password)-1] = '\0';

  if (line)
    free(line);

  return 1;

}
     

int socket_write(int sockfd, char *_sendline)
{
  int n=0;
  char sendline[MAXLINE+1];
	snprintf(sendline, MAXLINE, _sendline);
	n=write(sockfd, sendline, strlen(sendline));
  return n;

}

int SSL_socket_write(SSL *ssl, char *_sendline)
{
  int n=0;
  char sendline[MAXLINE+1];
	snprintf(sendline, MAXLINE, _sendline);
	n=SSL_write(ssl, sendline, strlen(sendline));
  return n;

}



char * socket_read(int sockfd,char *recvline)
{
  int n;

	n = read(sockfd, recvline, MAXLINE);
        recvline[n] = '\0';
	return recvline;
}

char * SSL_socket_read(SSL *ssl,char *recvline)
{
  int n;

	n = SSL_read(ssl, recvline, MAXLINE);
        recvline[n] = '\0';
	return recvline;
}



int main(void)
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


	int sockfd;
	struct sockaddr_in servaddr;

	char **pptr;
	//********** You can change. Put any values here *******
	char *hname = "smtp.gmail.com";

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


	fprintf(stderr, "%s\n", socket_read(sockfd,recvline));
        socket_write(sockfd,"EHLO big.mchirico.org\r\n");
	fprintf(stderr, "ehlo response:%s<-\n", socket_read(sockfd,recvline));


	socket_write(sockfd, "STARTTLS\r\n");
	fprintf(stderr, "response to starttls:%s<-\n", socket_read(sockfd,recvline));


	sbio = BIO_new_socket(sockfd, BIO_NOCLOSE);
	ssl = SSL_new(ctx);
	SSL_set_bio(ssl, sbio, sbio);
	SSL_set_connect_state(ssl);



	/* Circuit Breaker - NO encrypted connection */
	if (SSL_do_handshake(ssl) == 1) {
		fprintf(stderr, "SSL_do_handshake(ssl)=%d\n", 1);
	} else {
		fprintf(stderr, "SSL handshake error= %d\n",
			SSL_get_error(ssl, ret));
		fprintf(stderr,
			"Cannot establish an encrypted connection\nExiting\n\n");
		return -1;
	}



        SSL_socket_write(ssl,"EHLO mchirico.org\r\n");
        fprintf(stderr,"k: %s",SSL_socket_read(ssl,recvline));



	get_password("password_smtp_64", password, MAXLINE);

	snprintf(sendline, MAXLINE, "AUTH PLAIN %s\r\n", password); 
        fprintf(stderr,"password: ->%s<-\n",password);
        SSL_socket_write(ssl,sendline);
	fprintf(stderr, "login res: %s<-",SSL_socket_read(ssl,recvline));


        SSL_socket_write(ssl,"MAIL FROM: <mchirico@linuxaddicted.org>\r\n");
	fprintf(stderr, "2:%s",SSL_socket_read(ssl,recvline));


        SSL_socket_write(ssl,"RCPT TO: <mchirico@cwxstat.org>\r\n");
	fprintf(stderr, "3:%s", SSL_socket_read(ssl,recvline));
        
        SSL_socket_write(ssl,"RCPT TO: <Souptonuts@googlegroups.com>\r\n");
	fprintf(stderr, "3:%s", SSL_socket_read(ssl,recvline));

        SSL_socket_write(ssl,
          "DATA\r\nFrom: mchirico@linuxaddicted.org\r\n"
          "To: mchirico@cwxstat.org\r\n"
          "To: Souptonuts@googlegroups.com\r\n"
          "subject: Example using tlssmtp.c\r\n"
          "\r\nTest Send from tlssmtp.c"
          "\r\n.\r\n");
	fprintf(stderr, "4:%s", SSL_socket_read(ssl,recvline));


	fprintf(stderr, "5:%s", SSL_socket_read(ssl,recvline));

	SSL_shutdown(ssl);
	SSL_clear(ssl);

	fprintf(stderr, "SSL Connection closed\n");

	SSL_free(ssl);
	SSL_CTX_free(ctx);


	return 0;

}
