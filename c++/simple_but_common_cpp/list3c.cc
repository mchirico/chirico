/* Copyright (c) GPL mchirico@users.sourceforge.net

   Example if list using sort on a class
   with user defined comparison "cmp_t".

   compare this with list3b. This is much
   cleaner and does more.

   Downloads:
   http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <cctype> // this is for toupper()
#include <string>
#include <list>
#include <vector>
#include <cmath>
#define NUMPTS 6

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


class cmp_t {
  int i;
  int px;
  int py;
  int sizes;

public:
  cmp_t(int ii=0,int xx=0, int yy=0): i(ii),px(xx),py(yy),sizes(6) {}
  int size() { return sizes; }
  bool operator() (const  t*,const  t* y) const;
};

bool cmp_t::operator() (const t* x,const  t* y) const 
{

  switch(i) {
  case 0:
    return x->get_i() < y->get_i();
    break;
  case 1:
    return x->get_j() < y->get_j();
    break;
  case 2:
    return x->get_i() < y->get_j();
    break;
  case 3:
    return x->get_j() < y->get_i();
    break;
  case 4:
    return  ( x->get_i()-x->get_j() ) < ( y->get_i()-y->get_j() ) ;
    break;
  case 5:
    return  ( x->get_j()-x->get_i() ) < ( y->get_j()-y->get_i() ) ;
    break;
  case 6:
    return  sqrt(pow((double)(px-x->get_i()),2)+pow( (double) (py-x->get_j()),2))
                                   <
      sqrt(pow((double)(py-y->get_i()),2)+pow( (double) (py-y->get_j()),2)) ;
    break;
  default:
    return x->get_i() < y->get_i();
  }
}

class within_range: public unary_function<class t*,bool> {
  int px;
  int py;
  double d;
public:
  explicit within_range(int pxx=0, int pyy=0, double dist=1.0): px(pxx),py(pyy),d(dist) {}
  bool operator()(const t* tt) const {
   return sqrt(pow((double)(px-tt->get_i()),2)+pow( (double) (py-tt->get_j()),2)) < d;
  }
};

ostream& operator<<(ostream&s, const t* tt)
{
  return s << '(' << tt->get_i() << ',' << tt->get_j() << ')';
}


int main(void)
{

  list<t*> lst;
  
  vector<t> vpt;

  vpt.resize(NUMPTS);


  vpt[0].set_i(1);
  vpt[0].set_j(2);

  vpt[1].set_i(2);
  vpt[1].set_j(1);

  vpt[2].set_i(3);
  vpt[2].set_j(8);

  vpt[3].set_i(4);
  vpt[3].set_j(7);

  vpt[4].set_i(-3);
  vpt[4].set_j(7);

  vpt[5].set_i(12);
  vpt[5].set_j(12);

  cout << "vpt[0] " << &vpt[0] << endl << endl;


  for(unsigned int i=0; i<vpt.size(); ++i)
  lst.push_back(&vpt[i]);


  for(int i=0; i<=cmp_t().size(); ++i) {
    lst.sort(cmp_t(i));
    copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
    cout << endl << endl;
  }


  cout << endl << "** CHANGED vpt[4] ****" << endl;

  vpt[4].set_i(vpt[4].get_i()*10);
  vpt[4].set_j(vpt[4].get_j()*10);

  for(int i=0; i<=cmp_t().size(); ++i) {
    lst.sort(cmp_t(i));
    copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
    cout << endl << endl;
  }


    lst.sort(cmp_t(6,-30,70));
    copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
    cout << endl << endl;

    // Find point within the given range
    int my_px=3;
    int my_py=5;
    double range=3;
    list<t*>::iterator p = find_if(lst.begin(),lst.end(),within_range(my_px,my_py,range));
    if ( p != lst.end()) {
         cout << "First point within " << range 
           << " units of (" << my_px << ","
           << my_py << ") is " << *p << endl; 
       } else {
          cout << "NO points within " << range 
           << " units of (" << my_px << ","
           << my_py << ") " << endl;
      }
}





