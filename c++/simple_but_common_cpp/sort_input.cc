/* Copyright (c) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>

  Simple example of reading input as a string into a
  vector and sorting.

  $ ./sort_input  
    E F G H I
    ^d

    E
    F
    G
    H
    I



*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
int main(void)
{
  istream_iterator<string> in(cin);
  istream_iterator<string> eof;
  vector<string> v(in,eof);

  sort(v.begin(),v.end());
  copy(v.begin(),v.end(),ostream_iterator<string>(cout,"\n"));

}
