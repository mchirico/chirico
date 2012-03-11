#include "wrappert.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

extern int errno;
static void term_handler(int sig);
static void hup_handler(int sig);
static void load_config(void);
ssize_t WriteFile(int fd, const char *s);
static void *asyc_readInput(void *arg);
static void *asyc_write(void *arg);
/* static void *asyc_read(void *arg); */
static void process();




/* for asyc_write */
struct S_Buf {
	SSL *conn;
	char *s;
};




int init_conn(void)
{
	int i;
	pthread_t t;


	for (i = 0; i < CTBLMAX; ++i) {
		conntbl[i].conn = NULL;
		conntbl[i].t = 0;
		conntbl[i].FLAG = 0;
	}
	conn_count = -1;


	stop = 0;
	hup = 0;
	/* Register sighandlers */
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	/* Set handler for the ones we care about */
	sa.sa_handler = term_handler;
	sigaction(SIGTERM, &sa, NULL);
	sa.sa_handler = hup_handler;
	sigaction(SIGHUP, &sa, NULL);

	Pthread_create(&t, NULL, &asyc_readInput, NULL);

	return 0;
}

/*
 * SIGTERM handler
 */
static void term_handler(int sig)
{

	stop = 1;
}

/*
 * SIGHUP handler: re-read config
 */
static void hup_handler(int sig)
{
	hup = 1;
}

static void load_config(void)
{
	hup = 0;
}


static void process()
{
	pthread_t t;
	int i;
	struct S_Buf *s_b;

	Pthread_mutex_lock(&conn_mutex);
	strncpy(bbuf, bbuf2, BUF_LEN);
	Pthread_mutex_unlock(&conn_mutex);

	for (i = 0; i < CTBLMAX; ++i) {

		if (conntbl[i].FLAG != 0) {
#ifdef DEBUGPR                      
			syslog(LOG_ERR, "conntbl[%d].FLAG=%d", i,
			       conntbl[i].FLAG);
#endif
			Pthread_mutex_lock(&conn_mutex);
			s_b =
			    (struct S_Buf *) malloc(sizeof(struct S_Buf));
			Pthread_mutex_unlock(&conn_mutex);
			if (s_b == NULL) {
#ifdef DEBUGPR                      
				syslog(LOG_ERR, "s_b is NULL");
#endif
				return;
			}
			Pthread_mutex_lock(&conn_mutex);
			s_b->conn = conntbl[i].conn;
			Pthread_mutex_unlock(&conn_mutex);
			Pthread_create(&t, NULL, &asyc_write, s_b);

		}
	}
}




static void *asyc_write(void *arg)
{
	int err;
	SSL *conn;



	Pthread_mutex_lock(&conn_mutex);
	conn = ((struct S_Buf *) arg)->conn;
#ifdef DEBUGPR                      
	syslog(LOG_ERR, "asyc_write: (s address):%lu  strlen=%lu",
	       (size_t) bbuf, strlen(bbuf));
#endif
	err = SSL_write(conn, bbuf, strlen(bbuf));
#ifdef DEBUGPR                      
	syslog(LOG_ERR, " asyc_write(%d)[%ld]: %s<-", err, strlen(bbuf),
	       bbuf);
#endif
	free(arg);
	Pthread_mutex_unlock(&conn_mutex);

	Pthread_detach(pthread_self());
	return (NULL);
}

/*
static void *asyc_read(void *arg)
{
	int err, nread;
	SSL *conn;
	char buf[BUF_LEN];

	conn = ((struct S_Buf *) arg)->conn;

	do {
		for (nread = 0; nread < sizeof(buf); nread += err) {
			err =
			    SSL_read(conn, buf + nread,
				     sizeof(buf) - nread);
			if (err <= 0)
				break;
		}
	}
	while (err > 0);


	free(arg);
	Pthread_detach(pthread_self());
	return (NULL);
}
*/


static void *asyc_readInput(void *arg)
{


	do {
		load_config();
#ifdef DEBUGPR                      
		syslog(LOG_ERR, "fgets block\n");
#endif
		while (fgets(bbuf2, sizeof(bbuf2), stdin) && hup == 0
		       && stop == 0) {
#ifdef DEBUGPR                      
			syslog(LOG_ERR,
			       "fgets unblock. before process()\n");
#endif
			process();
		}
		*bbuf2 = '\0';

	} while (hup && stop == 0);
#ifdef DEBUGPR                      
	syslog(LOG_ERR, "Out of while\n");
#endif
	Pthread_detach(pthread_self());
	return (NULL);
}


int remove_conn(int me)
{
	if (me < 0)
		return (me);

	conntbl[me].conn = NULL;
	conntbl[me].t = 0;
	conntbl[me].FLAG = 0;
	conn_count--;

	return conn_count;

}



int assign_conn(void *arg)
{
	SSL *ssl = (SSL *) arg;
	int me = -1;
	int i;

	Pthread_mutex_lock(&conn_mutex);
	conn_count++;
	for (i = 0; i < CTBLMAX; ++i) {
		if (conntbl[i].FLAG == 0) {
			me = i;
		}
		if (me != -1)
			break;

	}
	if (me == -1) {
		/* Need to fix this */
		syslog(LOG_ERR, "too many connections\n");
		Pthread_mutex_unlock(&conn_mutex);
		return -1;
	}
	conntbl[me].conn = ssl;
	conntbl[me].t = pthread_self();
	conntbl[me].FLAG = 1;
	Pthread_mutex_unlock(&conn_mutex);

	syslog(LOG_ERR, "assign_conn completed\n");
	return me;
}

ssize_t WriteFile(int fd, const char *s)
{
	return write(fd, s, strlen(s));

}





/*
******************************************************************************************
******************************************************************************************
*/


void Pthread_attr_init(pthread_attr_t * attr)
{
	int n;

	if ((n = pthread_attr_init(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_attr_init error");
}

void Pthread_attr_destroy(pthread_attr_t * attr)
{
	int n;

	if ((n = pthread_attr_destroy(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_attr_destroy error");
}

void Pthread_attr_setdetachstate(pthread_attr_t * attr, int detach)
{
	int n;

	if ((n = pthread_attr_setdetachstate(attr, detach)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_attr_setdetachstate error");
}

void Pthread_attr_setscope(pthread_attr_t * attr, int scope)
{
	int n;

	if ((n = pthread_attr_setscope(attr, scope)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_attr_setscope error");
}

void
Pthread_create(pthread_t * tid, const pthread_attr_t * attr,
	       void *(*func) (void *), void *arg)
{
	int n;

	if ((n = pthread_create(tid, attr, func, arg)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_create error");
}

void Pthread_join(pthread_t tid, void **status)
{
	int n;

	if ((n = pthread_join(tid, status)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_join error");
}

void Pthread_detach(pthread_t tid)
{
	int n;

	if ((n = pthread_detach(tid)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_detach error");
}

void Pthread_kill(pthread_t tid, int signo)
{
	int n;

	if ((n = pthread_kill(tid, signo)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_kill error");
}

void Pthread_mutexattr_init(pthread_mutexattr_t * attr)
{
	int n;

	if ((n = pthread_mutexattr_init(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutexattr_init error");
}

void Pthread_mutexattr_destroy(pthread_mutexattr_t * attr)
{
	int n;

	if ((n = pthread_mutexattr_destroy(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutexattr_destroy error");
}

#ifdef	_POSIX_THREAD_PROCESS_SHARED
void Pthread_mutexattr_setpshared(pthread_mutexattr_t * attr, int flag)
{
	int n;

	if ((n = pthread_mutexattr_setpshared(attr, flag)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutexattr_setpshared error");
}
#endif

void Pthread_mutex_init(pthread_mutex_t * mptr, pthread_mutexattr_t * attr)
{
	int n;

	if ((n = pthread_mutex_init(mptr, attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutex_init error");
}

void Pthread_mutex_destroy(pthread_mutex_t * mptr)
{
	int n;

	if ((n = pthread_mutex_destroy(mptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutex_destroy error");
}

/* include Pthread_mutex_lock */
void Pthread_mutex_lock(pthread_mutex_t * mptr)
{
	int n;

	if ((n = pthread_mutex_lock(mptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutex_lock error");
}

/* end Pthread_mutex_lock */

void Pthread_mutex_unlock(pthread_mutex_t * mptr)
{
	int n;

	if ((n = pthread_mutex_unlock(mptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_mutex_unlock error");
}

void Pthread_condattr_init(pthread_condattr_t * attr)
{
	int n;

	if ((n = pthread_condattr_init(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_condattr_init error");
}

void Pthread_condattr_destroy(pthread_condattr_t * attr)
{
	int n;

	if ((n = pthread_condattr_destroy(attr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_condattr_destroy error");
}

#ifdef	_POSIX_THREAD_PROCESS_SHARED
void Pthread_condattr_setpshared(pthread_condattr_t * attr, int flag)
{
	int n;

	if ((n = pthread_condattr_setpshared(attr, flag)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_condattr_setpshared error");
}
#endif

void Pthread_cond_broadcast(pthread_cond_t * cptr)
{
	int n;

	if ((n = pthread_cond_broadcast(cptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_cond_broadcast error");
}

void Pthread_cond_signal(pthread_cond_t * cptr)
{
	int n;

	if ((n = pthread_cond_signal(cptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_cond_signal error");
}

void Pthread_cond_wait(pthread_cond_t * cptr, pthread_mutex_t * mptr)
{
	int n;

	if ((n = pthread_cond_wait(cptr, mptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_cond_wait error");
}

void
Pthread_cond_timedwait(pthread_cond_t * cptr, pthread_mutex_t * mptr,
		       const struct timespec *tsptr)
{
	int n;

	if ((n = pthread_cond_timedwait(cptr, mptr, tsptr)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_cond_timedwait error");
}

void Pthread_once(pthread_once_t * ptr, void (*func) (void))
{
	int n;

	if ((n = pthread_once(ptr, func)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_once error");
}

void Pthread_key_create(pthread_key_t * key, void (*func) (void *))
{
	int n;

	if ((n = pthread_key_create(key, func)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_key_create error");
}

void Pthread_setcancelstate(int state, int *oldstate)
{
	int n;

	if ((n = pthread_setcancelstate(state, oldstate)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_setcancelstate error");
}

void Pthread_setspecific(pthread_key_t key, const void *value)
{
	int n;

	if ((n = pthread_setspecific(key, value)) == 0)
		return;
	errno = n;
	syslog(LOG_ERR, "pthread_setspecific error");
}

/* include pr_thread_id */
long pr_thread_id(pthread_t * ptr)
{
#if defined(sun)
	return ((ptr == NULL) ? pthread_self() : *ptr);	/* Solaris */

#elif defined(__osf__) && defined(__alpha)
	pthread_t tid;

	tid = (ptr == NULL) ? pthread_self() : *ptr;	/* Digital Unix */
	return (pthread_getsequence_np(tid));
#else
	/* 4everything else */
	return ((ptr == NULL) ? pthread_self() : *ptr);
#endif
}
