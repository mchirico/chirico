/* Copyright (c) GPL mchirico@users.sourceforge.net

    Transform(....,Pred class) uses the Pred class
 in a pass by value fashion.

    Transform is great for cleaning memory with delete

 Download: http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

*/


#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <list>
#include <vector>


#define NUM 5

using namespace std;

class t {
  int i;
  int j;
public:
  t(int ii=0,int jj=0):i(ii),j(jj) {}
  void  set_i(int ii) { i=ii; }
  int  get_i() const { return i; }

  void  set_j(int jj) { j=jj; }
  int  get_j() const { return j; }
};

class myrange_bool: public unary_function<class t*,bool> {
  int count;
  int limit_count;
  int i;
  int j;
public:
  explicit myrange_bool(int limit_c=3,int ii=7, int jj=20): count(0),limit_count(limit_c),i(ii),j(jj) {}
  bool operator() (const t* tt)  {
    ++count;
    return tt->get_i() < i  &&  tt->get_j() < j &&  count < limit_count ;
  }
};

class myrange: public unary_function<class t*, class t*> {
  int count;
  int limit_count;
  int i;
  int j;
public:
  explicit myrange(int limit_c=3,int ii=7, int jj=20): count(0),limit_count(limit_c),i(ii),j(jj) {}
   t* operator() (const t* tt)  {
    t* mt = new t();
    ++count;
    if (tt->get_i() < i  &&  tt->get_j() < j &&  count < limit_count)
      {
        mt->set_i(tt->get_i());
        mt->set_j(tt->get_j());
      }else {
        mt->set_i(0);
        mt->set_j(0);
      }
    return mt;
  }
};

ostream& operator<<(ostream&s, const t* tt)
{
  return s << '(' << tt->get_i() << ',' << tt->get_j() << ')';
}

template<class In, class Out, class Pred>
Out copy_if(In first, In last, Out res, Pred p)
{
  while (first != last) {
    if(p(*first))*res++=*first;
    ++first;
  }
  return res;
}


struct Delete_ptr {
  template<class T> T* operator() (T* p) const {delete p; return 0; }
};


int main(void)
{
  list<t*> lst;
  vector<t*> v;
  vector<t*> v2;


  for(int i=0; i<NUM; ++i)
    {
     t* pt= new t();
     pt->set_i(4+i);
     pt->set_j(12+i);
     lst.push_back(pt);
    }

  copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
  cout << endl;

  copy_if(lst.begin(),lst.end(),back_inserter(v),myrange_bool());
  copy(v.begin(),v.end(),ostream_iterator<t*>(cout," "));
  cout << endl;
  
  transform(lst.begin(),lst.end(),back_inserter(v2),myrange());
  copy(v2.begin(),v2.end(),ostream_iterator<t*>(cout," "));
  cout << endl;


  // Note only do this for lst and v2. Other is shared.
  transform(lst.begin(),lst.end(),lst.begin(),Delete_ptr());
  transform(v2.begin(),v2.end(),lst.begin(),Delete_ptr());

  return 0;
}





