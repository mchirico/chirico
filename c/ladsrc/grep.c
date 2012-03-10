/* grep.c - Limited reimplementation of the grep command */

#include <alloca.h>
#include <ctype.h>
#include <popt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MODE_REGEXP	    1
#define MODE_EXTENDED	    2
#define MODE_FIXED	    3

void do_regerror(int errcode, const regex_t *preg) { 
    char *errbuf;
    size_t errbuf_size;

    errbuf_size = regerror(errcode, preg, NULL, 0);
    errbuf = alloca(errbuf_size);
    if (!errbuf) {
        perror("alloca");
        return;
    }

    regerror(errcode, preg, errbuf, errbuf_size);
    fprintf(stderr, "%s\n", errbuf);
}

int scanFile(FILE * f, int mode, const void * pattern, 
	     int ignoreCase, const char * fileName, 
	     int * maxCountPtr) {
    long lineLength;
    char * line;
    int match;
    int rc;
    char * chptr;
    char * prefix = "";

    if (fileName) {
	prefix = alloca(strlen(fileName) + 4);
	sprintf(prefix, "%s: ", fileName);
    }

    lineLength = sysconf(_SC_LINE_MAX);
    line = alloca(lineLength);

    while (fgets(line, lineLength, f) && (*maxCountPtr)) {
	/* if we don't have a final '\n' we didn't get the 
	   whole line */
	if (line[strlen(line) - 1] != '\n') {
	    fprintf(stderr, "%sline too long\n", prefix);
	    return 1;
	}

	if (mode == MODE_FIXED) {
	    if (ignoreCase) {
		for (chptr = line; *chptr; chptr++) {
		    if (isalpha(*chptr)) *chptr = tolower(*chptr);
		}
	    }
	    match = (strstr(line, pattern) != NULL);
	} else {
	    match = 0;
	    rc = regexec(pattern, line, 0, NULL, 0);
	    if (!rc)
		match = 1;
	    else if (rc != REG_NOMATCH)
		do_regerror(match, pattern);
	}

	if (match) {
	    printf("%s%s", prefix, line);
	    if (*maxCountPtr > 0)
		(*maxCountPtr)--;
	}
    }

    return 0;
}

int main(int argc, const char ** argv) {
    const char * pattern = NULL;
    regex_t regPattern;
    const void * finalPattern;
    int mode = MODE_REGEXP;
    int ignoreCase = 0;
    int maxCount = -1;
    int rc;
    int regFlags;
    const char ** files;
    poptContext optCon;
    FILE * f;
    char * chptr;
    struct poptOption optionsTable[] = { 
	    { "extended-regexp", 'E', POPT_ARG_VAL, 
	      &mode, MODE_EXTENDED,
	      "pattern for match is an extended regular "
	      "expression" },
	    { "fixed-strings", 'F', POPT_ARG_VAL, 
	      &mode, MODE_FIXED,
	      "pattern for match is a basic string (not a "
	      "regular expression)", NULL },
	    { "basic-regexp", 'G', POPT_ARG_VAL, 
	      &mode, MODE_REGEXP,
	      "pattern for match is a basic regular expression" },
	    { "ignore-case", 'i', POPT_ARG_NONE, &ignoreCase, 0,
	      "perform case insensitive search", NULL },
	    { "max-count", 'm', POPT_ARG_INT, &maxCount, 0,
	      "terminate after N matches", "N" },
            { "regexp", 'e', POPT_ARG_STRING, &pattern, 0,
              "regular expression to search for", "pattern" },
	    POPT_AUTOHELP
	    { NULL, '\0', POPT_ARG_NONE, NULL, 0, NULL, NULL }
    }; 

    optCon = poptGetContext("grep", argc, argv, optionsTable, 0);
    poptSetOtherOptionHelp(optCon, "<pattern> <file list>");

    if ((rc = poptGetNextOpt(optCon)) < -1) {
        /* an error occurred during option processing */
        fprintf(stderr, "%s: %s\n", 
                poptBadOption(optCon, POPT_BADOPTION_NOALIAS),
                poptStrerror(rc));
        return 1;
    }

    files = poptGetArgs(optCon);
    /* if we weren't given a pattern it must be the first 
       leftover */
    if (!files && !pattern) {
	poptPrintUsage(optCon, stdout, 0);
	return 1;
    }

    if (!pattern) {
	pattern = files[0];
	files++;
    }

    regFlags = REG_NEWLINE | REG_NOSUB;
    if (ignoreCase) {
	regFlags |= REG_ICASE;
	/* convert the pattern to lower case; this doesn't matter
	   if we're ignoring the case in a regular expression, but
	   it lets strstr() handle -i properly */
	chptr = alloca(strlen(pattern) + 1);
	strcpy(chptr, pattern);
	pattern = chptr;

	while (*chptr) {
	    if (isalpha(*chptr)) *chptr = tolower(*chptr);
	    chptr++;
	}
    }


    switch (mode) {
    case MODE_EXTENDED:
        regFlags |= REG_EXTENDED;
    case MODE_REGEXP:
        if ((rc = regcomp(&regPattern, pattern, regFlags))) {
	    do_regerror(rc, &regPattern);
	    return 1;
	}
	finalPattern = &regPattern;
	break;

    case MODE_FIXED:
        finalPattern = pattern;
	break;
    }

    if (!*files) {
	rc = scanFile(stdin, mode, finalPattern, ignoreCase, NULL,
		      &maxCount);
    } else if (!files[1]) {
	/* this is handled separately because the file name should
	   not be printed */
	if (!(f = fopen(*files, "r"))) {
	    perror(*files);
	    rc = 1;
	} else {
	    rc = scanFile(f, mode, finalPattern, ignoreCase, NULL,
			  &maxCount);
	    fclose(f);
	}
    } else {
	rc = 0;

	while (*files) {
	    if (!(f = fopen(*files, "r"))) {
		perror(*files);
		rc = 1;
	    } else {
		rc |= scanFile(f, mode, finalPattern, ignoreCase, 
			       *files, &maxCount);
		fclose(f);
	    }
	    files++;
	    if (!maxCount) break;
	}
    }

    return rc;
}
