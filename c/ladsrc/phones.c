/* phones.c - Telephone number database built using db library */

/* This implements a very simple phone database. Full usage 
   information is given in the text. */

#include <alloca.h>
#include <depot.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(void) {
    fprintf(stderr, "usage: phones -a [-f] <name> <phone>\n");
    fprintf(stderr, "              -d <name>\n");
    fprintf(stderr, "              -q <name>\n");
    fprintf(stderr, "              -l\n");
    exit(1);
}

/* Opens the database $HOME/.phonedb. If writeable is nonzero,
   the database is opened for updating. If writeable is 0, the
   database is opened read-only. */
DEPOT * openDatabase(int writeable) {
    DEPOT * dp;
    char * filename;
    int flags;

    /* Set the open mode */
    if (writeable) {
        flags = DP_OWRITER | DP_OCREAT;
    } else {
        flags = DP_OREADER;
    }

    filename = alloca(strlen(getenv("HOME")) + 20);
    strcpy(filename, getenv("HOME"));
    strcat(filename, "/.phonedb");

    dp = dpopen(filename, flags, 0);
    if (!dp) {
        fprintf(stderr, "failed to open %s: %s\n", filename, 
                dperrmsg(dpecode));
        return NULL;
    }

    return dp;
}

/* add a new record to the database; this parses the
   command-line arguments directly */
int addRecord(int argc, char ** argv) {
    DEPOT * dp;
    char * name, * phone;
    int rc = 0;
    int overwrite = 0;
    int flag;
   
    /* check for our parameters; -f means overwrite an
       existing entry, and the name and phone number should
       be all that remains */
    if (!argc) usage();
    if (!strcmp(argv[0], "-f")) {
        overwrite = 1;
        argc--, argv++;
    }

    if (argc != 2) usage();

    name = argv[0];
    phone = argv[1];

    /* open the database for writing */
    if (!(dp = openDatabase(1))) return 1;

    /* if we shouldn't overwrite an existing entry, check
       to see if this name is already used */
    if (!overwrite) {
	flag = DP_DKEEP;
    } else {
	flag = DP_DOVER;
    }

    if (!dpput(dp, name, -1, phone, -1, flag)) {
	if (dpecode == DP_EKEEP) {
	    fprintf(stderr, "%s already has a listing\n", name);
	} else {
	    fprintf(stderr, "put failed: %s\n", dperrmsg(dpecode));
	}

	rc = 1;
    }

    dpclose(dp);

    return rc;
}

/* looks up a name, and prints the phone number associated
   with it; parses the command line directly */
int queryRecord(int argc, char ** argv) {
    DEPOT * dp;
    int rc;
    char * phone;

    /* only one argument is expected, a name to look up */
    if (argc != 1) usage();

    /* open the database for reading */
    if (!(dp = openDatabase(0))) return 1;

    phone = dpget(dp, argv[0], -1, 0, -1, NULL);
    if (!phone) {
	if (dpecode == DP_ENOITEM)
	    fprintf(stderr, "%s is not listed\n", argv[0]);
	else
	    fprintf(stderr, "error reading database: %s\n",
                    dperrmsg(dpecode));

        rc = 1;
    } else {
        printf("%s %s\n", argv[0], (char *) phone);
        rc = 0;
    }

    dpclose(dp);

    return rc;
}

/* delete the specified record; the name is passed as a
   command-line argument */
int delRecord(int argc, char ** argv) {
    DEPOT * dp;
    int rc;

    /* only a single argument is expected */
    if (argc != 1) usage();

    /* open the database for updating */
    if (!(dp = openDatabase(1))) return 1;

    if (!(rc = dpout(dp, argv[0], -1))) {
	if (dpecode == DP_ENOITEM) 
	    fprintf(stderr, "%s is not listed\n", argv[0]);
	else
	    fprintf(stderr, "error removing item: %s\n",
                    dperrmsg(dpecode));
	    
        rc = 1;
    }

    dpclose(dp);

    return rc;
}

/* lists all of the records in the database */
int listRecords(void) {
    DEPOT * dp;
    char * key, * value;

    /* open the database read-only */
    if (!(dp = openDatabase(0))) return 1;

    dpiterinit(dp);

    /* iterate over all of the records */
    while ((key = dpiternext(dp, NULL))) {
	value = dpget(dp, key, -1, 0, -1, NULL);
        printf("%s %s\n", key, value);
    }

    dpclose(dp);

    return 0;
}

int main(int argc, char ** argv) {
    if (argc == 1) usage();

    /* look for a mode flag, and call the appropriate function
       with the remainder of the arguments */
    if (!strcmp(argv[1], "-a")) 
        return addRecord(argc - 2, argv + 2);
    else if (!strcmp(argv[1], "-q")) 
        return queryRecord(argc - 2, argv + 2);
    else if (!strcmp(argv[1], "-d")) 
        return delRecord(argc - 2, argv + 2);
    else if (!strcmp(argv[1], "-l")) {
        if (argc != 2) usage();
        return listRecords();
    }

    usage();  /* did not recognize any options */
    return 0; /* doesn't get here due to usage() */
}
