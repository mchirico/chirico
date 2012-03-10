#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}


static int xBusy(void *pArg, int nBusy){
  fprintf(stderr,"Here is an error %d\n",nBusy);
  sqlite3_sleep(50);
  return 1;             /* Try again... */
}


int main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;


  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    exit(1);
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }

  
  // From what I can tell, either this function is used
  // or sqlite3_busy_handler is used. Agreed. Some code
  // shows these being used together, but is that correct?
  /*
  int ms = 2000;
  sqlite3_busy_timeout(db, ms);
  */

  rc =  sqlite3_busy_handler(db, xBusy, 0);
  fprintf(stderr,"rc = %d\n\n",rc);
  rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return 0;
}
