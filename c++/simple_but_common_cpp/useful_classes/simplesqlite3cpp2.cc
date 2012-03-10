/*
  Very simple C program.

   Compile:
     gcc -o simplesqlite3cpp2 simplesqlite3cpp2.cc  -Wall -W -O2 -Wl,-R/usr/local/lib -lsqlite3

   Usage:

       ./simplesqlite3cpp2 test.db "create table emp (name varchar(15),age int,weight double)"
       ./simplesqlite3cpp2 test.db "insert into emp (name,age,weight) values ('Bob',47,172)"
       ./simplesqlite3cpp2 test.db "insert into emp (name,age,weight) values ('Sue',38,134)"

       ./simplesqlite3cpp2 test.db "select * from emp"

       Headings                                        
       name    age     weight                          
                                                       
       Data                                            
       Bob     47      172     Sue     38      134     





  
   Note sqlite3 shared library, by default, installs in /usr/local/lib. 
   The compile command above will directly link the full path of 
   this library into this program.

*/

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
			s_exe.c_str(),       /* SQL to be executed */
			&result,       /* Result written to a char *[]  that this points to */
			&nrow,             /* Number of result rows written here */
			&ncol,          /* Number of result columns written here */
			&zErrMsg          /* Error msg written here */
			);

      vcol_head.clear();
      vdata.clear();

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
  } 
};

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

