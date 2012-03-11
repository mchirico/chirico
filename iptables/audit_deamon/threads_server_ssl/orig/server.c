#include "common.h"
 
void do_server_loop(BIO *conn)
{
    int  err, nread;
    char buf[80];
 
    do
    {
        for (nread = 0;  nread < sizeof(buf);  nread += err)
        {
             err = BIO_read(conn, buf + nread, sizeof(buf) - nread);
             if (err <= 0)
                 break;
        }
        fprintf(stdout, "%s", buf);
    }
    while (err > 0);
}
 
void THREAD_CC server_thread(void *arg)
{
    BIO *client = (BIO *)arg;
 
#ifndef WIN32
    pthread_detach(pthread_self(  ));
#endif
    fprintf(stderr, "Connection opened.\n");
    do_server_loop(client);
    fprintf(stderr, "Connection closed.\n");

    BIO_free(client);
    ERR_remove_state(0);

}
 
int main(int argc, char *argv[])
{
    BIO         *acc, *client;
    THREAD_TYPE tid;
 
    init_OpenSSL(  );
 
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
        THREAD_CREATE(tid, (void *)server_thread, client);
    }
 
    BIO_free(acc);
    return 0;
}

