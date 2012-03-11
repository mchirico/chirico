#include "common.h"
 
#define CERTFILE "server.pem"
SSL_CTX *setup_server_ctx(void)
{
    SSL_CTX *ctx;

    ctx = SSL_CTX_new(SSLv23_method(  ));
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1)
        int_error("Error loading certificate from file");
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE, SSL_FILETYPE_PEM) != 1)
        int_error("Error loading private key from file");
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

#ifndef WIN32
    pthread_detach(pthread_self(  ));
#endif
    if (SSL_accept(ssl) <= 0)
        int_error("Error accepting SSL connection");
    fprintf(stderr, "SSL Connection opened\n");
    if (do_server_loop(ssl))
        SSL_shutdown(ssl);
    else
        SSL_clear(ssl);
    fprintf(stderr, "SSL Connection closed\n");
    SSL_free(ssl);

    ERR_remove_state(0);

#ifdef WIN32
    _endthread(  );
#endif
}
 
int main(int argc, char *argv[])
{
    BIO         *acc, *client;
    SSL         *ssl;
    SSL_CTX     *ctx;
    THREAD_TYPE tid;
 
    init_OpenSSL(  );
    seed_prng(  );

    ctx = setup_server_ctx(  );

    acc = BIO_new_accept(PORT);
    if (!acc)
        int_error("Error creating server socket");
 
    if (BIO_do_accept(acc) <= 0)
        int_error("Error binding server socket");
 
    for (;;)
    {
        if (BIO_do_accept(acc) <= 0)
            int_error("Error accepting connection");
 
        client = BIO_pop(acc);
        if (!(ssl = SSL_new(ctx)))
            int_error("Error creating SSL context");

        SSL_set_bio(ssl, client, client);
        THREAD_CREATE(tid, (void *)server_thread, ssl);
    }
    
    SSL_CTX_free(ctx);
    BIO_free(acc);
    return 0;
}

