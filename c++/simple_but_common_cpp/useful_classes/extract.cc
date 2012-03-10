/* CopyRight GPL
   mmc Mike Chirico mchirico@users.sourceforge.net
   
   C++ string splitting routine

Download:
http://prdownloads.sourceforge.net/cpearls/perl_like_.0.0.3.tar.gz?download

*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

#include "extract.h"



int main(void)
{



    extract e(" \n.");
    std::string s;

    e.setdelims(", ");
    e.strip("(1,2,(3,4),((5,6,(8,3),2)),1)");
    std::cout << "e.F(): " << e.F() << std::endl;
    std::cout << "e.NF(): " << e.NF() << std::endl << std::endl;
    std::cout << "e.TL(): " << e.TL() << std::endl;
    std::cout << e.I(1) << std::endl;

    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;



    e.setdelims(", ");
    e.strip("1");
    std::cout << "e.F(): " << e.F() << std::endl;
    std::cout << "e.NF(): " << e.NF() << std::endl << std::endl;
    std::cout << "e.TL(): " << e.TL() << std::endl;
    std::cout << e.I(1) << std::endl;

    std::cout << std::endl << std::endl;













    s=e.F();
    e.setdelims("(),");
    e.strip(s);
    std::cout << std::endl << std::endl;
    std::cout << "e.F(): " << e.F() << std::endl;
    std::cout << "e.TL(): " << e.TL() << std::endl;
    std::stringstream ss;
    std::stringstream ss2;
    ss.str("");
    double k;
    double sum=0;
    int count=0;
    std::string del="";
    copy(e.BEGIN(),e.END(),std::ostream_iterator<std::string>(ss," "));
    ss2 << "(";
    while(ss >> k) 
      { 
        ++count; sum+=k;
	ss2 << del <<  "(" << count << "," << sum << ")";
	del=",";
      }
    ss2 << ")";
    std::cout << ss2.str();
  
    //    std::cout << "--" << e.v[4] << "--" << std::endl;








}

