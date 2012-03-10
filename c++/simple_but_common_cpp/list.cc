/* Copyright (c) GPL mchirico@users.sourceforge.net

   Example if list and list functions

      .sort
      .unique
      .merge
      .reverse

*/


#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <string>
#include <list>

using namespace std;


class str_equal: public unary_function< string, bool>  {
  string s;  
public:

  explicit str_equal(const string& ss): s(ss) {} 
  bool operator()(const string& ls) const { return ls== s;}

};



int main(void)
{

  list<string> spacer;
  list<string> lst;
  list<string> lst2;


  spacer.push_front("\n");

  lst.push_front("shoe");
  lst.push_front("box");
  lst.push_front("box");  //two boxes
  lst.push_front("rubber duck");
  lst.push_front("coat");

  lst2.push_front("apple");
  lst2.push_front("pear");
  lst2.push_front("peach");


  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));

  lst.unique(); //this get rid of the second box
  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));

  lst.sort();
  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));


  lst.remove("rubber duck");
  lst.push_back("rubber chicken");
  lst.sort();
  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));

  
  list<string>::iterator p = find_if(lst.begin(),lst.end(),str_equal("rubber chicken"));
  lst.splice(p,lst2,lst2.begin(),lst2.end());
  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));

  lst.reverse();
  copy(lst.begin(),lst.end(),ostream_iterator<string>(cout,"\n"));
  copy(spacer.begin(),spacer.end(),ostream_iterator<string>(cout,"\n"));


}




