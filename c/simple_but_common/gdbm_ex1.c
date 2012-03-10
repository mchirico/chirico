/*
  Simple gdbm example.

  This is how you compile

      $ gcc gdbm_ex1.c -lgdbm -o gdbm_ex1


  Format of the datum struct:

      typedef struct {
                 char *dptr;
                 int  dsize;
              } datum;


*/


#include <stdio.h>
#include <gdbm.h>



int main (void)
{
  GDBM_FILE dbf;
  datum key = { "testkey", 7 };     /* key, length */
  datum value = { "testvalue", 9 }; /* value, length */
  datum content;

  printf ("Storing key-value pair... ");
  dbf = gdbm_open ("test", 0, GDBM_NEWDB, 0644, 0);
  gdbm_store (dbf, key, value, GDBM_INSERT);
  gdbm_close (dbf);


  dbf = gdbm_open ("test", 0, GDBM_READER, 0644, 0);
  content = gdbm_fetch(dbf, key);
  printf("\n Output %s\n",content.dptr);
  printf ("done.\n");
  gdbm_close (dbf);


  return 0;
}
