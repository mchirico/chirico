/* popt-lib.c - Library which provides a popt table for nesting */

#include <popt.h>
#include <stdlib.h>

struct params {
    int height, width;
    char * fg, * bg;
};

static void callback(poptContext con, 
		     enum poptCallbackReason reason,
		     const struct poptOption * opt, 
		     const char * arg,
		     const void * data);

/* Store the parsed variables here. A global is not normally
   preferred, but it is simpler. */
struct params ourParam;

struct poptOption libTable[] = {
    { NULL, '\0', 
      POPT_ARG_CALLBACK | POPT_CBFLAG_PRE | POPT_CBFLAG_POST, 
      callback, '\0', (void *) &ourParam, NULL },
    { "height", 'h', POPT_ARG_STRING, NULL, '\0', NULL, NULL },
    { "width", 'w', POPT_ARG_STRING, NULL, '\0', NULL, NULL },
    { "fg", 'f', POPT_ARG_STRING, NULL, '\0', NULL, NULL },
    { "bg", 'b', POPT_ARG_STRING, NULL, '\0', NULL, NULL },
    { NULL, '\0', POPT_ARG_NONE, NULL, '\0', NULL, NULL }
};

static void callback(poptContext con, 
		     enum poptCallbackReason reason,
		     const struct poptOption * opt, 
		     const char * arg,
		     const void * data) {
    struct params * p = (void *) data;
    char * chptr = NULL;

    if (reason == POPT_CALLBACK_REASON_PRE) {
	p->height = 640;
	p->width = 480;
	p->fg = "white";
	p->bg = "black";
    } else if (reason == POPT_CALLBACK_REASON_POST) {
	printf("using height %d width %d fg %s bg %s\n",
	       p->height, p->width, p->fg, p->bg);

    } else {
	switch (opt->shortName) {
	    case 'h': p->height = strtol(arg, &chptr, 10); break;
	    case 'w': p->width = strtol(arg, &chptr, 10); break;
	    case 'f': p->fg = (char *) arg; break;
	    case 'b': p->bg = (char *) arg; break;
	}

	if (chptr && *chptr) {
	    fprintf(stderr, "numeric argument expected for %s\n", 
		    opt->longName);
	    exit(1);
	}
    }
}

