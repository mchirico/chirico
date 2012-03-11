#include <stdio.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>

#include "clientlib.h"

/* This is an example program that shows how easy it is to
 * write a audispd plugin. It shows the basic items that a
 * plugin is expected to follow. You should handle SIGTERM
 * and SIGHUP. The events come from stdin.
 */

/* Global Data */
volatile int stop = 0;
volatile int hup = 0;

#define BUF_LEN 1025




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


char *mtoken(char *buf, char *beg_str, char *end_str)
{
	char *t, *e;
	t = strstr(buf, beg_str);
	if (t != NULL) {
		e = strstr(t, end_str);
		if (e != NULL) {
			*e = '\0';
			t = t + strlen(beg_str);
			return t;
		}
	}
	return NULL;

}





int process(char *buf)
{
	char *t, *t1, *t2, *e;
	char *addr;
	char *acct;

	t = strstr(buf, "type=USER_LOGIN");
	t1 = strstr(buf, "res=failed");
	t2 = strstr(buf, "addr=");

	if (t != NULL && t1 != NULL && t2 != NULL) {
		syslog(LOG_ERR, " chirico plugin: %s", buf);
		// Fix addr must come before acct
		addr = mtoken(buf, "addr=", ",");
		acct = mtoken(buf, "acct=", ":");
		if (addr == NULL)
			return 0;
		if (acct == NULL)
			return 0;
	} else {
		return 0;
	}

	// acct="bozo":
	if (t2 != NULL) {
		e = strstr(t2, ",");
		if (e != NULL)
			*e = '\0';
	}


	if (t != NULL && t1 != NULL && t2 != NULL) {
		/* We need some type of rate limiting */
		if (rate(0, 53400) == 1) {
			syslog(LOG_ERR,
			       " chirico <calling doclient>: %s %s", addr,
			       acct);
			doclient(addr, acct);
		}
	}
	return 0;
}



int main(int argc, char *argv[])
{
	char buf[BUF_LEN];
	char *p = " ";
	struct sigaction sa;

	/* This plugin takes 1 argument to tell you which plugin it is */
	if (argc > 1)
		p = argv[1];

	/* Register sighandlers */
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	/* Set handler for the ones we care about */
	sa.sa_handler = term_handler;
	sigaction(SIGTERM, &sa, NULL);
	sa.sa_handler = hup_handler;
	sigaction(SIGHUP, &sa, NULL);

	do {
		/* Load configuration */
		load_config();
                syslog(LOG_ERR, "%s plugin: %s", p,"active");

		/* Now the event loop */
		while (fgets(buf, sizeof(buf), stdin) && hup == 0 && stop == 0) {
			//syslog(LOG_ERR, "%s plugin: %s", p, buf);
			process(buf);
		}
		*buf = '\0';
	} while (hup && stop == 0);
	return 0;
}
