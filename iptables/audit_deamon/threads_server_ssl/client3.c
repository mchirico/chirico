#include "common.h"
#include <unistd.h>

#define CIPHER_LIST "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
#define CAFILE "/etc/banssh/rootcert.pem"
#define CADIR "/etc/banssh"
#define CERTFILE "/etc/banssh/client.pem"
SSL_CTX *setup_client_ctx(void)
{
	SSL_CTX *ctx;

	ctx = SSL_CTX_new(SSLv23_method());
	if (SSL_CTX_load_verify_locations(ctx, CAFILE, CADIR) != 1)
		int_error("Error loading CA file and/or directory");
	if (SSL_CTX_set_default_verify_paths(ctx) != 1)
		int_error
		    ("Error loading default CA file and/or directory");
	if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1)
		int_error("Error loading certificate from file");
	if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE, SSL_FILETYPE_PEM) !=
	    1)
		int_error("Error loading private key from file");
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	SSL_CTX_set_verify_depth(ctx, 4);
	SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2);
	if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST) != 1)
		int_error("Error setting cipher list (no valid ciphers)");
	return ctx;
}

int do_client_loop(SSL * ssl)
{
	int err, nread;
	char buf[1024];
	buf[0] = '\0';


	do {

		/* Maybe this is causing problems? Yeah, I think it is correct now */
		for (nread = 0; nread < sizeof(buf); nread += err) {
			err =
			    SSL_read(ssl, buf + nread,
				     sizeof(buf) - nread);
			buf[nread + err] = '\0';
			fprintf(stderr, "%s", buf + nread);
			/*  fprintf(stderr, "\n[sizeof(buf)=%lu,nread=%d,err=%d]\n",sizeof(buf),nread,err); */
			if (err <= 0)
				break;
		}


	} while (err > 0);
	return 1;
}

int main_ssl(int argc, char **argv)
{
	BIO *conn;
	SSL *ssl;
	SSL_CTX *ctx;
	long err;

	init_OpenSSL();
	seed_prng();

	ctx = setup_client_ctx();

	fprintf(stderr, "SERVER= %s:%s\n", SERVER, PORT);
	conn = BIO_new_connect(SERVER ":" PORT);
	if (!conn)
		int_error("Error creating connection BIO");

	if (BIO_do_connect(conn) <= 0)
		int_error("Error connecting to remote machine");

	ssl = SSL_new(ctx);
	SSL_set_bio(ssl, conn, conn);
	if (SSL_connect(ssl) <= 0)
		int_error("Error connecting SSL object");
	if ((err = post_connection_check(ssl, SERVER)) != X509_V_OK) {
		fprintf(stderr, "-Error: peer certificate: %s\n",
			X509_verify_cert_error_string(err));
		int_error("Error checking SSL object after connection");
	}
	fprintf(stderr, "SSL Connection opened\n");
	if (do_client_loop(ssl))
		SSL_shutdown(ssl);
	else
		SSL_clear(ssl);
	fprintf(stderr, "SSL Connection closed\n");

	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return 0;
}

int main(int argc, char **argv)
{
	int i = 0, j = 0;
	/* This for loop is is the connection gets dropped.
	   We're the client, and we need to try and connect to the server */
	for (j = 0; j < 1000; ++j) {
		for (i = 0; i < 200; ++i) {
			main_ssl(argc, argv);
			sleep(2 * i);
		}
	}


	return 0;
}
