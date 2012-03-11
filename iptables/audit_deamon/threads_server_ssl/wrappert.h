#ifndef WRAPPERT_H
#define WRAPPERT_H

#include <pthread.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>


#include <signal.h>
#include <syslog.h>

/* Global Data */
volatile int stop;
volatile int hup;
struct sigaction sa;

#define BUF_LEN 1025
char bbuf[BUF_LEN];
char bbuf2[BUF_LEN];


typedef struct CONNTBL CONNTBL;


pthread_mutex_t conn_mutex;
#define CTBLMAX 9



struct CONNTBL {
	/* int conn; */
	SSL *conn;
	pthread_t t;
	int fd;
	int FLAG;
};
int conn_count;
CONNTBL conntbl[CTBLMAX];


int init_conn(void);
int remove_conn(int me);


/*  dev stuff */
int assign_conn(void *arg);




/* prototypes for wrapper functions */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

void Pthread_attr_init(pthread_attr_t *);
void Pthread_attr_destroy(pthread_attr_t *);
void Pthread_attr_setdetachstate(pthread_attr_t *, int);
void Pthread_attr_setscope(pthread_attr_t *, int);
void Pthread_create(pthread_t *, const pthread_attr_t *,
		    void *(*)(void *), void *);
void Pthread_join(pthread_t, void **);
void Pthread_detach(pthread_t);
void Pthread_kill(pthread_t, int);
void Pthread_setcancelstate(int, int *);

void Pthread_mutexattr_init(pthread_mutexattr_t *);
void Pthread_mutexattr_destroy(pthread_mutexattr_t *);
void Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void Pthread_mutex_destroy(pthread_mutex_t *);
void Pthread_mutex_lock(pthread_mutex_t *);
void Pthread_mutex_unlock(pthread_mutex_t *);

void Pthread_condattr_init(pthread_condattr_t *);
void Pthread_condattr_destroy(pthread_condattr_t *);
void Pthread_condattr_setpshared(pthread_condattr_t *, int);
void Pthread_cond_broadcast(pthread_cond_t *);
void Pthread_cond_signal(pthread_cond_t *);
void Pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
void Pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *,
			    const struct timespec *);

void Pthread_key_create(pthread_key_t *, void (*)(void *));
void Pthread_setspecific(pthread_key_t, const void *);
void Pthread_once(pthread_once_t *, void (*)(void));

#endif				/* WRAPPERT_H */
