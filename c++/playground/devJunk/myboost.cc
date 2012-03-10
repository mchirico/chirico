/*
Compile this as follows:
  g++ myboost.cc -lboost_regex


*/

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "boost/regex.hpp"
int main(void)
{
  boost::regex  expression("[0-9][0-9]*");
  boost::smatch m;
  string s="one 34 or this 3"
         "more time"
         "3mmm2m"
    "my end";

  while(boost::regex_search(s,m,expression,boost::match_not_dot_newline))
    {
      cout << m << endl;
      s=m.suffix();

    }
  return 0;
}
