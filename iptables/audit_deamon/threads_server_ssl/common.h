#ifndef COMMON_H
#define COMMON_H

#include <syslog.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>
#include "reentrant.h"


#include <pthread.h>
#define THREAD_CC
#define THREAD_TYPE                    pthread_t
#define THREAD_CREATE(tid, entry, arg) pthread_create(&(tid), NULL, \
                                                      (entry), (arg))


#define PORT            "16001"
#define SERVER          "localhost"
#define CLIENT          "localhost"

#define int_error(msg)  handle_error(__FILE__, __LINE__, msg)
void handle_error(const char *file, int lineno, const char *msg);

void init_OpenSSL(void);

int verify_callback(int ok, X509_STORE_CTX * store);

long post_connection_check(SSL * ssl, char *host);

void seed_prng(void);

#endif				/* COMMON_H */
