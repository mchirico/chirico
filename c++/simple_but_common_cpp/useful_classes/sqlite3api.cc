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
