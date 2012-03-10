/* popt-nest.c - Example of using a nested popt table from a library */

#include <popt.h>

/* this would normally be declared in a header file */
extern struct poptOption libTable[];

int main(int argc, const char * argv[]) {
    poptContext optCon;
    int rc;
    struct poptOption options[] = {
	{ "app1", '\0', POPT_ARG_NONE, NULL, '\0' },
	{ NULL, '\0', POPT_ARG_INCLUDE_TABLE, libTable, 
	  '\0', "Nested:", },
	POPT_AUTOHELP
	{ NULL, '\0', POPT_ARG_NONE, NULL, '\0' }
    };

    optCon = poptGetContext("popt-nest", argc, argv, options, 0);

    if ((rc = poptGetNextOpt(optCon)) < -1) {
        fprintf(stderr, "%s: %s\n", 
                poptBadOption(optCon, POPT_BADOPTION_NOALIAS),
                poptStrerror(rc));
        return 1;
    }

    return 0;
}
