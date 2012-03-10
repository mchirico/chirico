/* Copyright (c) GPL 2006 by Mike Chirico <mchirico@users.sourceforge.net>

   This demonstrates some uses of first_first_of and find_first_not_of


*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;


string  mffo(string &s,const string &delm,string::size_type &_pos )
{


  string::size_type pos = _pos;
  string::size_type pend = 0;

  pos=s.find_first_not_of(delm,pos);

  pend=s.find_first_of(delm,pos);
  _pos=pend;
  if (pos != string::npos && pend != string::npos ) {
    return s.substr(pos,pend-pos);
  }
  if (pos != string::npos && pend == string::npos ) {
    return s.substr(pos,s.length()-pos);
  }
  if (pos == string::npos)
    {
      _pos=string::npos;
    return "";
    }



}

int main(void)
{
  string s;
  vector<string> v;
  string::size_type pos=0;

  cout << "Start typing. ^d to end." << endl;

  while(getline(cin,s,'\n'))
    {
      v.push_back(s);
      while(pos != string::npos) {
      cout << " ->" << mffo(s," ,;",pos) << "<--" << endl;
      }
      pos=0;

    }


  copy(v.begin(),v.end(),ostream_iterator<string>(cout,"\n"));

}
