#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "mysqlite3.h"
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

