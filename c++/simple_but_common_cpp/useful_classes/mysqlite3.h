
#ifndef SQLITE3_H
#define SQLITE3_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

class SQLITE3 {
private:
  sqlite3 *db;
  char *zErrMsg;
  char **result;
  int rc;
  int nrow,ncol;
  int db_open;

public:

  std::vector<std::string> vcol_head;
  std::vector<std::string> vdata;


  SQLITE3 (std::string tablename="init.db"): zErrMsg(0), rc(0),db_open(0) {
    rc = sqlite3_open(tablename.c_str(), &db);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      sqlite3_close(db);
    }
    db_open=1;
  }

  int exe(std::string s_exe) {
      rc = sqlite3_get_table(
			db,              /* An open database */
			s_exe.c_str(),   /* SQL to be executed */
			&result,         /* Result written to a char *[]  that this points to */
			&nrow,           /* Number of result rows written here */
			&ncol,           /* Number of result columns written here */
			&zErrMsg         /* Error msg written here */
			);

      if (vcol_head.size() > 0)
	{ 
         vcol_head.clear();
	}

      if (vdata.size() > 0)
	{ 
         vdata.clear();
	}

     if( rc == SQLITE_OK ){
      for(int i=0; i < ncol; ++i)
	vcol_head.push_back(result[i]); /* First row heading */
      for(int i=0; i < ncol*nrow; ++i)
	vdata.push_back(result[ncol+i]);
     }
     sqlite3_free_table(result);
      return rc;
  }

  ~SQLITE3(){
      sqlite3_close(db);
      //fprintf(stderr,"Database closed\n");
  } 
};

class SQLite3Handle {
 public:
  explicit SQLite3Handle(SQLITE3 *conn): r_(conn) {}
  ~SQLite3Handle() { delete r_; }
  SQLITE3 *sptr() { return r_; }
 private:
  SQLite3Handle( const SQLite3Handle &);
  SQLite3Handle &operator = (const SQLite3Handle &);
  SQLITE3 *r_;
};



/* Sample usage without handler
#include <mysqlite3.h>
int main(int argc, char **argv){
  if( argc!=3 ){
   std::cerr << "Usage: " << argv[0] << " DATABASE SQL-STATEMENT" << std::endl;
   exit(1);
  }
  SQLITE3 sql(argv[1]);
  sql.exe(argv[2]);

  if( sql.vcol_head.size() > 0 )
    {
      std::cout << "Headings" << std::endl;
      copy(sql.vcol_head.begin(),sql.vcol_head.end(),std::ostream_iterator<std::string>(std::cout,"\t")); 
      std::cout << std::endl << std::endl;
      std::cout << "Data" << std::endl;
      copy(sql.vdata.begin(),sql.vdata.end(),std::ostream_iterator<std::string>(std::cout,"\t")); 
      std::cout << std::endl;
    }

  return 0;
}
*/


/* Sample usage with handler
#include <mysqlite3.h>
int main(int argc, char **argv){
  if( argc!=3 ){
   std::cerr << "Usage: " << argv[0] << " DATABASE SQL-STATEMENT" << std::endl;
   exit(1);
  }
  

   SQLite3Handle conn(new SQLITE3("../threads_server/weathersqliter2"));
   conn.sptr()->exe("argv[2]");



  if( conn.sptr()->vcol_head.size() > 0 )
    {
      std::cout << "Headings" << std::endl;
      copy(conn.sptr()->vcol_head.begin(),conn.sptr()->vcol_head.end(),std::ostream_iterator<std::string>(std::cout,"\t")); 
      std::cout << std::endl << std::endl;
      std::cout << "Data" << std::endl;
      copy(conn.sptr()->vdata.begin(),conn.sptr()->vdata.end(),std::ostream_iterator<std::string>(std::cout,"\t")); 
      std::cout << std::endl;
    }

  return 0;
}
*/



#endif
