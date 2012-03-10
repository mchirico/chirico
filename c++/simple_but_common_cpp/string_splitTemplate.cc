/*
  This is a more general form for STL that
  support push_back (list,vector)

*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
#include <algorithm>
using namespace std;

bool space(char c)
{
  return isspace(c);
}

bool not_space(char c)
{
  return !isspace(c);
}



template <template <typename T> class C>
C<string> split(const string& s)
{
  typedef string::const_iterator str_iter;
  C<string> r;

  str_iter i = s.begin();
  str_iter End = s.end();
  while( i != End ) {

    i = find_if(i, End, not_space);
    str_iter j = find_if(i, End, space);
    if ( i != End)
      r.push_back(string(i,j));
    i=j;
  }
  return r;
}


int main(void)
{
  string s;
  s="text here to print";

  vector<string> v=split< vector >(s);
  list<string> l=split<list>(s);
  deque<string> d=split<deque>(s);

  copy(v.begin(),v.end(),ostream_iterator<string>(cout,"\n"));
  cout << endl << endl;
  copy(l.begin(),l.end(),ostream_iterator<string>(cout,"\n"));
  cout << endl << endl;
  copy(d.begin(),d.end(),ostream_iterator<string>(cout,"\n"));
}
