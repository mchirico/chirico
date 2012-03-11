#include "common.h"
 
DH *dh512 = NULL;
DH *dh1024 = NULL;

void init_dhparams(void)
{
    BIO *bio;

    bio = BIO_new_file("dh512.pem", "r");
    if (!bio)
        int_error("Error opening file dh512.pem");
    dh512 = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    if (!dh512)
        int_error("Error reading DH parameters from dh512.pem");
    BIO_free(bio);

    bio = BIO_new_file("dh1024.pem", "r");
    if (!bio)
        int_error("Error opening file dh1024.pem");
    dh1024 = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    if (!dh1024)
        int_error("Error reading DH parameters from dh1024.pem");
    BIO_free(bio);
}

DH *tmp_dh_callback(SSL *ssl, int is_export, int keylength)
{
    DH *ret;

    if (!dh512 || !dh1024)
        init_dhparams(  );

    switch (keylength)
    {
        case 512:
            ret = dh512;
            break;
        case 1024:
        default: /* generating DH params is too costly to do on the fly */
            ret = dh1024;
            break;
    }
    return ret;
}

#define CIPHER_LIST "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
#define CAFILE "rootcert.pem"
#define CADIR NULL
#define CERTFILE "server.pem"
SSL_CTX *setup_server_ctx(void)
{
    SSL_CTX *ctx;
 
    ctx = SSL_CTX_new(SSLv23_method(  ));
    if (SSL_CTX_load_verify_locations(ctx, CAFILE, CADIR) != 1)
        int_error("Error loading CA file and/or directory");
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
        int_error("Error loading default CA file and/or directory");
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1)
        int_error("Error loading certificate from file");
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE, SSL_FILETYPE_PEM) != 1)
        int_error("Error loading private key from file");
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
                       verify_callback);
    SSL_CTX_set_verify_depth(ctx, 4);
    SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 |
                             SSL_OP_SINGLE_DH_USE);
    SSL_CTX_set_tmp_dh_callback(ctx, tmp_dh_callback);
    if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST) != 1)
        int_error("Error setting cipher list (no valid ciphers)");
    return ctx;
}

int do_server_loop(SSL *ssl)
{
    int  err, nread;
    char buf[80];
 
    do
    {
        for (nread = 0;  nread < sizeof(buf);  nread += err)
        {
            err = SSL_read(ssl, buf + nread, sizeof(buf) - nread);
            if (err <= 0)
                break;
        }
        fprintf(stdout, "%s", buf);
    }
    while (err > 0);
    return (SSL_get_shutdown(ssl) & SSL_RECEIVED_SHUTDOWN) ? 1 : 0;
}
  
void THREAD_CC server_thread(void *arg)
{
    SSL *ssl = (SSL *)arg;
    long err;
 

    pthread_detach(pthread_self(  ));
    if (SSL_accept(ssl) <= 0)
        int_error("Error accepting SSL connection");
    if ((err = post_connection_check(ssl, CLIENT)) != X509_V_OK)
    {
        fprintf(stderr, "-Error: peer certificate: %s\n",
                X509_verify_cert_error_string(err));
        int_error("Error checking SSL object after connection");
    }
    fprintf(stderr, "SSL Connection opened\n");
    if (do_server_loop(ssl))
        SSL_shutdown(ssl);
    else
        SSL_clear(ssl);
    fprintf(stderr, "SSL Connection closed\n");
    SSL_free(ssl);
    ERR_remove_state(0);

}
 
int main(int argc, char *argv[])
{
    BIO     *acc, *client;
    SSL     *ssl;
    SSL_CTX *ctx;
    THREAD_TYPE tid;

    init_OpenSSL(  );
    seed_prng();

 
    ctx = setup_server_ctx(  );
 
    acc = BIO_new_accept(PORT);
    if (!acc)
        int_error("Error creating server socket");
 
    if (BIO_do_accept(acc) <= 0)
        int_error("Error binding server socket");
 
    while(1)
    {
        if (BIO_do_accept(acc) <= 0)
            int_error("Error accepting connection");
 
        client = BIO_pop(acc);
        if (!(ssl = SSL_new(ctx)))
        int_error("Error creating SSL context");
        SSL_set_accept_state(ssl);
        SSL_set_bio(ssl, client, client);
        THREAD_CREATE(tid, (void *)server_thread, ssl);
    }
 
    SSL_CTX_free(ctx);
    BIO_free(acc);
    return 0;
}

