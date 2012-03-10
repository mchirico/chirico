/* Copyright (c) GPL Mike Chirico mchirico@comcast.net

 Example of string, char with new and delete.

   Note delete[] for new []; otherwise if new is used without []
   then delete must match.   

   Check this out ourself by removing "[]"  from delete below.

   Also demonstrated is the getline function. Unlike cin >> str,
   the getline allows the spaces between "Bob Anderson" to be
   entered.

 Compile:
   g++ -o string_and_char -Wall -W -O2 -s -pipe  string_and_char.cc

 Run with Valgrind:
   valgrind --logfile=valgrind.output   --tool=memcheck ./string_and_char 


*/

#include <iostream>
#include <string>
using namespace std;

char* c_string(const string& s)
{
  char* p = new char[s.length()+1];  // Creating with new and using []
  p[s.copy(p,string::npos)]=0; //This adds terminator
  return p;
}

int main(void)
{
  string b="beg -->";
  string e="<-- end";
  string str;
  cout << "Enter your name: ";
  getline(cin,str);

  char* p;
  p=c_string(b+str+e);

  cout << p << endl;
  delete[] p; // Since created with new [] must delete with delete[]
}
