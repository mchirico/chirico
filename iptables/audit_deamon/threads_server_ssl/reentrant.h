#ifndef REENTRANT_H
#define REENTRANT_H


#include <unistd.h>
#include <pthread.h>
#include <openssl/ssl.h>

int THREAD_setup(void);
int THREAD_cleanup(void);

#endif				/* REENTRANT_H */
