#include "common.h"

void do_client_loop(BIO *conn)
{
    int  err, nwritten;
    char buf[80];

    for (;;)
    {
        if (!fgets(buf, sizeof(buf), stdin))
            break;
        for (nwritten = 0;  nwritten < sizeof(buf);  nwritten += err)
        {
            err = BIO_write(conn, buf + nwritten, sizeof(buf) - nwritten);
            if (err <= 0)
                return;
        }
    }
}

int main(int argc, char *argv[])
{
    BIO  *conn;

    init_OpenSSL();

    conn = BIO_new_connect(SERVER ":" PORT);
    if (!conn)
        int_error("Error creating connection BIO");

    if (BIO_do_connect(conn) <= 0)
        int_error("Error connecting to remote machine");

    fprintf(stderr, "Connection opened\n");
    do_client_loop(conn);
    fprintf(stderr, "Connection closed\n");

    BIO_free(conn);
    return 0;
}

