/* find.c - A restricted reimplementation of find which uses \codefn{nftw()} */

#define _XOPEN_SOURCE 600

#include <fnmatch.h>
#include <ftw.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * name = NULL;
int minDepth = 0, maxDepth = INT_MAX;

int find(const char * file, const struct stat * sb, int flags,
	 struct FTW * f) {
    if (f->level < minDepth) return 0;
    if (f->level > maxDepth) return 0;
    if (name && fnmatch(name, file + f->base, FNM_PERIOD)) return 0;

    if (flags == FTW_DNR) {
	fprintf(stderr, "find: %s: permission denied\n", file);
    } else {
	printf("%s\n", file);
    }

    return 0;
}

int main(int argc, const char ** argv) {
    int flags = FTW_PHYS;
    int i;
    int problem = 0;
    int tmp;
    int rc;
    char * chptr;

    /* look for first command line parameter (which must occur after
       the list of paths */
    i = 1;
    while (i < argc && *argv[i] != '-') i++;

    /* handle the command line options */
    while (i < argc && !problem) {
	if (!strcmp(argv[i], "-name")) {
	    i++;
	    if (i == argc)
		problem = 1;
	    else
		name = argv[i++];
	} else if (!strcmp(argv[i], "-depth")) {
	    i++;
	    flags |= FTW_DEPTH;
	} else if (!strcmp(argv[i], "-mount") || 
		   !strcmp(argv[i], "-xdev")) {
	    i++;
	    flags |= FTW_MOUNT;
	} else if (!strcmp(argv[i], "-mindepth") ||
	           !strcmp(argv[i], "-maxdepth")) {
	    i++;
	    if (i == argc)
		problem = 1;
	    else {
		tmp = strtoul(argv[i++], &chptr, 10);
		if (*chptr)
		    problem = 1;
		else if (!strcmp(argv[i - 2], "-mindepth"))
		    minDepth = tmp;
		else
		    maxDepth = tmp;
	    }
	}
    }

    if (problem) {
	fprintf(stderr, "usage: find <paths> [-name <str>] "
	        "[-mindepth <int>] [-maxdepth <int>]\n");
	fprintf(stderr, "       [-xdev] [-depth]\n");
	return 1;
    }

    if (argc == 1 || *argv[1] == '-') {
	argv[1] = ".";
	argc = 2;
    }

    rc = 0;
    i = 1;
    flags =0;
    while (i < argc && *argv[i] != '-') 
	rc |= nftw(argv[i++], find, 100, flags);

    return rc;
}
