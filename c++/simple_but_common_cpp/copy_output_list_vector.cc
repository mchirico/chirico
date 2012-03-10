/* Copyright (c) GPL Mike Chirico  
   Ref: simple_but_common_cpp

  This copy command can be preferred to the for command
  in efficiency -- there is no temp variable.

  Below is an efficient output if you do not need to
  flush the buffer.  "\n" is preferred to endl, since
  endl will flush the buffer.

*/

#include <iostream>
#include <list>
#include <vector>
#include <iterator>

using namespace std;
int main(void)
{
  vector<int> v;
  list<int> l;

  v.push_back(1);
  v.push_back(2);
  copy(v.begin(),v.end(),ostream_iterator<int>(cout,"\n"));


  l.push_back(23);
  l.push_back(12);
  copy(l.begin(),l.end(),ostream_iterator<int>(cout,"\n"));

}

