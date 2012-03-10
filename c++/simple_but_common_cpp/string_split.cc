#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
using namespace std;

void split(const string& s, char c,
           vector<string>& v) {

  string::size_type i=0;
  string::size_type j= s.find(c);

  while(j != string::npos ) {
    v.push_back(s.substr(i,j-i));
    i = ++j;
    j = s.find(c,j);
  }
  if (j == string::npos)
    v.push_back(s.substr(i, s.length()));

}

int main(void)
{
  vector<string> v;
  string s = "one,two,three";

  split(s,',',v);
  copy(v.begin(),v.end(),ostream_iterator<string>(cout,"\n"));



}

