
/* Copyright (c) 2004 GPL mmc Mike Chirico mchirico@users.sourceforge.net
http://prdownloads.sourceforge.net/cpearls/sqlite_examples.tar.gz?download
Updated: Tue Sep 21 11:47:21 EDT 2004

 Compile:
  gcc -o eatblob eatblob.c -lsqlite3

 Usage:


    You can interactively  execute the following (arrows ">" represent the
                 output from the program)


            $ ./eatblob test3.db test.png
	    create table test (a varchar(50), b blob);
	   >Total Changes 0
	    insert into test (a,b) values ('test',?);
	   >Total Changes 1
	    select a,b from test;
	   >IN BLOB bytes 5552
	   >test
	   >Total Changes 1
            ^D

     Or, put all the sql commands in the file "sqlcommands", ';' delimited so
     that you have the following:


           $ cat sqlcommands

              create table blobtest (des varchar(80),b blob);
              insert into blobtest (des,b)
                       values ('A test file: test.png',?);
              select * from  blobtest;

      Then, run eatblob as follows:

           $ ./eatblob test3.db test.png < sqlcommands

      Or, do everything on the command prompt

           $ ./eatblob test3.db test.png "create table blobtest (des varchar(80),b blob);"
           $ ./eatblob test3.db test.png "insert into blobtest (des,b) values ('A test file: test.png',?);"


     Thanks to Steven R. <stevenr@columbus.rr.com> for fixing the addmem routine. This
     program should match the documentation at
        http://souptonuts.sourceforge.net/readme_sqlite_tutorial.html




*/

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sqlite3.h>
#define STMLEN 1024

extern int errno;

#define MULT_START     16384
#define MULT_INCREMENT 2
#define INIT_SIZE      1024

long memindx = MULT_START;
long memnext;


ssize_t mygetline(char **lineptr, size_t * n, FILE * stream)
{
    ssize_t mread;
    char *line = NULL;
    char *head = NULL;

    line = *lineptr;




    if ((mread = getline(&line, n, stream)) > 0) {
        head = line;
        line = line + mread - 1;


        if (head[0] == '\n') {
            *lineptr = head;
            return mread;
        }


        if (head[0] == '.' && head[1] == 'q') {
            return -1;
        }
        if (head[0] == '.' && head[1] == 'e') {
            return -1;
        }


        if (strcspn(head, ";") < (size_t) mread) {
            *lineptr = head;
            return mread;

        }


        if ((mread = getdelim(&line, n, ';', stream)) < 0) {
            fprintf(stderr, "ERROR in mygetline getdelm \n");
        }


    }


    *lineptr = head;
    return mread;
}




long addmem(char **buf, long size)
{


    memnext = (size > 0) ? size + memindx : INIT_SIZE;
    memindx = memindx * MULT_INCREMENT;
    char *tbuf = realloc(*buf, memnext);

    if (tbuf == NULL) {
        fprintf(stderr, "Can't allocate memory in addmem\n");
        return size;
    } else {
        *buf = tbuf;
        return memnext;
    }

}


int print_col(sqlite3_stmt * pTableInfo, int col)
{

    int fd;
    static int ct = 0;
    char outfile[50];

    switch (sqlite3_column_type(pTableInfo, col)) {
    case SQLITE_INTEGER:
        printf("%d ", sqlite3_column_int(pTableInfo, col));
        break;
    case SQLITE_FLOAT:
        printf("%f ", sqlite3_column_double(pTableInfo, col));
        break;
    case SQLITE_TEXT:
        printf("%s ", sqlite3_column_text(pTableInfo, col));
        break;
    case SQLITE_BLOB:	//printf("%s",sqlite3_column_blob(pTableInfo, col));
        /* fprintf(stderr, "IN BLOB bytes %d\n",
           sqlite3_column_bytes(pTableInfo, col)); */
        snprintf(outfile, 20, "outdata.%d.png", ct++);
        if ((fd = open(outfile, O_RDWR | O_CREAT, 0600)) == -1) {
            fprintf(stderr, "Can't open data: %s\n",
                    strerror(errno));
            return 1;
        }

        write(fd, sqlite3_column_blob(pTableInfo, col),
              sqlite3_column_bytes(pTableInfo, col));
        close(fd);

        break;
    case SQLITE_NULL:
        printf("Null ");
        break;
    default:
        printf(" *Cannot determine SQLITE TYPE* col=%d ", col);
    }

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3 *db;
    sqlite3_stmt *plineInfo = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t mread;

    int fd, n;
    long buflen = 0, totread = 0;
    char *buf = NULL, *pbuf = NULL;

    //  char *zErrMsg = 0;
    int rc, i;

    if (argc < 3) {
        fprintf(stderr,
                "Usage: %s <DATABASE> <BINARYFILE> < sqlcommands \n\n"
                "Or, the following:\n\n"
                "  $%s test3.db test.png \n"

                "   eatblob:0> create table blobtest (des varchar(80), b blob);\n"
                "   eatblob:0> insert into blobtest (des,b) values ('A test file: test.png',?);\n"
                "   eatblob:1> select * from blobtest;\n"
                "    A test file: test.png\n"
                "   eatblob:1>\n\n"
                " Note output.0.png will contain a copy of test.png\n\n"
                "Or, do everything on the command prompt:\n\n"
                " $ ./eatblob test3.db test.png \"create table blobtest (des varchar(80),b blob);\"\n"
                " $ ./eatblob test3.db test.png \"insert into blobtest (des,b) values ('A test file: test.png',?);\"\n"
                "\n\n",
                argv[0], argv[0]);
        exit(1);
    }

    if (sqlite3_open(argv[1], &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: \n");
        sqlite3_close(db);
        exit(1);
    }

    if ((fd = open(argv[2], O_RDWR | O_CREAT, 0600)) == -1) {
        fprintf(stderr, "Can't open data: %s\n", strerror(errno));
        return 1;
    }

    while (buflen - totread - 1 < 1024)
        buflen = addmem(&buf, buflen);
    pbuf = buf;
    totread = 0;
    while ((n = read(fd, pbuf, 1024)) > 0) {
        totread += n;
        pbuf[n] = '\0';	// This is for printing test
        while (buflen - totread - 1 < 1024)
            buflen = addmem(&buf, buflen);

        pbuf = &buf[totread];

    }
    close(fd);


    if (argc == 4) {
        rc = sqlite3_prepare(db, argv[3], -1, &plineInfo, 0);
        if (rc == SQLITE_OK && plineInfo != NULL) {
            //fprintf(stderr, "SQLITE_OK\n");
            sqlite3_bind_blob(plineInfo, 1, buf, totread,
                              free);
            while ((rc =
                        sqlite3_step(plineInfo)) == SQLITE_ROW) {
                //
                for (i = 0;
                        i < sqlite3_column_count(plineInfo);
                        ++i)
                    print_col(plineInfo, i);

                printf("\n");

            }
            rc = sqlite3_finalize(plineInfo);
        }
        fprintf(stderr, "eatblob:%d> ", sqlite3_total_changes(db));

    } else {
        fprintf(stderr, "eatblob:0> ");
        while ((mread = mygetline(&line, &len, stdin)) > 0) {
            rc = sqlite3_prepare(db, line, -1, &plineInfo, 0);
            if (rc == SQLITE_OK && plineInfo != NULL) {
                //fprintf(stderr, "SQLITE_OK\n");
                sqlite3_bind_blob(plineInfo, 1, buf,
                                  totread, free);
                while ((rc =
                            sqlite3_step(plineInfo)) ==
                        SQLITE_ROW) {
                    //
                    for (i = 0;
                            i <
                            sqlite3_column_count
                            (plineInfo); ++i)
                        print_col(plineInfo, i);

                    printf("\n");

                }
                rc = sqlite3_finalize(plineInfo);
            }
            fprintf(stderr, "eatblob:%d> ",
                    sqlite3_total_changes(db));
        }		/* end of while */

    }

    if (line) {
        free(line);
    }
    sqlite3_close(db);
    return 0;
}
