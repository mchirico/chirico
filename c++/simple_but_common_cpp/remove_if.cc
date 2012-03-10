/*
   Note if you call remove_if twice you will get into
   trouble because you cannot guarantee what will
   be at the end of remove.

   remove_if brings all elements to the front that
   do not match the remove. The other elements could
   be malformed.
   
   Always call remove_if with erase, or you will get
   something that you do not want!

*/


#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

bool mt(const string& s)
{
  return s != "no";
}

int main(void)
{

  vector<string> v;


  v.push_back("more");
  v.push_back("stuff");
  v.push_back("no");

 copy(v.begin(),v.end(),ostream_iterator<string>(cout," "));
 cout << endl;

 // DO NOT DO THIS -- note have no is copied twice ************
 cout << "\n DO NOT CALL  remove_if(v.begin(),v.end(),mt),v.end()\n"
      << " and expect it to be the same list after position mark\n" 
      << " You should see 'no' twice below\n" 
      << endl;
 remove_if(v.begin(),v.end(),mt),v.end();
 copy(v.begin(),v.end(),ostream_iterator<string>(cout," "));
 cout << endl << endl;
 // END OF BAD IDEAT ****************

 v.erase(remove_if(v.begin(),v.end(),mt),v.end());


 copy(v.begin(),v.end(),ostream_iterator<string>(cout," "));
 cout << endl;

   
 copy(v.begin(),v.end(),ostream_iterator<string>(cout," "));
 cout << endl;



}
