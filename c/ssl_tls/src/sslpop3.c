/*  Copyright (C) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>



  If you're using postfix,  in the file /etc/postfix/main.cf
  make the following changes:

         smtpd_tls_loglevel = 2

  When this client connect to your postfix server, you'll
  want to see if there are any problems.

  Don't forget to restart postfix.



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

     POP3
        http://www.faqs.org/rfcs/rfc1939.html


     POP3 Command Summary

        USER name       valid in the AUTHORIZATION state
        PASS string
        QUIT

        STAT
        LIST [msg]
        RETR msg
        DELE msg
        NOOP
        RSET
        QUIT
        
        



Command that works
openssl s_client -connect pop.gmail.com:995

*/



#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>


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
#include <fcntl.h>




#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  200
#define LISTENQ         1024


#define CAFILE "rootcert.pem"
#define CADIR NULL
#define CERTFILE "client.pem"




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
	int err=0, depth=0, mydata_index=0;
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

	/* Quick note here. If you 

           a. Return 1 the connection will be accepted
	   b. Return 0 the connection will be rejected

	*/

        preverify_ok = 1;
	return 1;
}


SSL_CTX *setup_client_ctx(void)
{
	SSL_CTX *ctx;
	ctx = SSL_CTX_new(SSLv23_method());


	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	return ctx;
}


int get_password(char *file,char *password, int len)
{
  int fp,n;
  
  if((fp=open(file, O_RDONLY|O_CREAT, 0600)) == -1)
    {
      fprintf(stderr,"Can't open password_file: %s\n",strerror(errno));
      fprintf(stderr,"File password_file created but you need to add a password\n");
      exit(0);
    }

  n=read(fp,password,len);
  if (n > 4 && password[n-1] == '\n')
    password[n-1]='\0'; /* no \n in password */

  password[n]='\0';

  if (strlen(password) < 3 )
    {
      fprintf(stderr,"Gmail requires password length of 4 or more\n");
      exit(0);
    }



  return 0;

}


int main(void)
{

	BIO *sbio;
	SSL *ssl;
	SSL_CTX *ctx;
        int ret=0;
	ssize_t n;

	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
        char password[MAXLINE +1];

	SSL_library_init();
	RAND_load_file("/dev/urandom", 1024);

	ctx = setup_client_ctx();

	/* Now doing standard connect stuff */



	int sockfd;
	struct sockaddr_in servaddr;

	char **pptr;
	//********** You can change. Put any values here *******
	char *hname = "pop.gmail.com";
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
	servaddr.sin_port = htons(995);
	inet_pton(AF_INET, str, &servaddr.sin_addr);

	connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
	// Chirico - this is the old stuff
	// process_smtp(sockfd, hname, page, poststr);

	/*
	snprintf(sendline, MAXLINE, "STAT\r\n");
	write(sockfd, sendline, strlen(sendline));
	*/


        /* Move this */
        get_password("password_file",password,MAXLINE);
        fprintf(stderr,"password ->%s<-\n",password);

	sbio = BIO_new_socket(sockfd, BIO_NOCLOSE);
	ssl = SSL_new(ctx);
	SSL_set_bio(ssl, sbio, sbio);
	SSL_set_connect_state(ssl);



        /* Circuit Breaker - NO encrypted connection */
        if(SSL_do_handshake(ssl) > 0) 
	  {
            fprintf(stderr,"SSL_do_handshake(ssl)=%d\n",1);
	  } else
          {
	    fprintf(stderr,"SSL handshake error= %d\n",SSL_get_error(ssl,ret));
	    fprintf(stderr,"Cannot establish an encrypted connection\nExiting\n\n");
            return -1;
          }



	n = SSL_read(ssl, sendline, 1024);
	sendline[n] = '\0';
	fprintf(stderr, "%s", sendline);


	snprintf(sendline, 1024, "USER smtpsnd@gmail.com\r\n");
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, sendline, 1024);
	sendline[n] = '\0';
	fprintf(stderr, "%s", sendline);

	/* password */




	snprintf(sendline, 1024, "PASS %s\r\n",password);
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	fprintf(stderr, "%s", recvline);


	snprintf(sendline, 1024, "LIST\r\n");
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	fprintf(stderr, "%s", recvline);



	snprintf(sendline, 1024, "TOP 1 19\r\n");
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	fprintf(stderr, "%s", recvline);


	snprintf(sendline, 1024, "RETR 1\r\n");
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	fprintf(stderr, "%s", recvline);

	snprintf(sendline, 1024, "QUIT\r\n");
	SSL_write(ssl, sendline, strlen(sendline));
	n = SSL_read(ssl, recvline, MAXLINE);
	recvline[n] = '\0';
	fprintf(stderr, "%s", recvline);



	SSL_shutdown(ssl);
	SSL_clear(ssl);

	fprintf(stderr, "SSL Connection closed\n");

	SSL_free(ssl);
	SSL_CTX_free(ctx);


	return 0;

}
