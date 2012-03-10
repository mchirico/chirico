/* Copyright (c) GPL mchirico@users.sourceforge.net

   Example if list using sort on a class
   with user defined comparison "cmp_t".

   You will want to take a look at list3c.cc
   for how all of this can be done with vectors.


*/


#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <cmath>
#define NUMPTS 5

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

public:
  cmp_t(int ii=0,int xx=0, int yy=0): i(ii),px(xx),py(yy) {}

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


ostream& operator<<(ostream&s, const t* tt)
{
  return s << '(' << tt->get_i() << ',' << tt->get_j() << ')';
}



int main(void)
{

  list<t*> lst;
  t *pt[NUMPTS];


 
  pt[0]=new t(1,2);
  pt[1]=new t(2,1);
  pt[2]=new t(3,8);
  pt[3]=new t(4,7);
  pt[4]=new t(-3,7);


  for(int i=0; i<NUMPTS; ++i)
  lst.push_back(pt[i]);



  for(int i=0; i<=6; ++i) {
    lst.sort(cmp_t(i));
    copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
    cout << endl << endl;
  }



  cout << endl << "** CHANGED pt[4] ****" << endl;

  pt[4]->set_i(pt[4]->get_i()*10);
  pt[4]->set_j(pt[4]->get_j()*10);



  for(int i=0; i<=6; ++i) {
    lst.sort(cmp_t(i));
    copy(lst.begin(),lst.end(),ostream_iterator<t*>(cout," "));
    cout << endl << endl;
  }


  // house keeping
  lst.clear();
  for(int i=0; i<NUMPTS; ++i)
    delete pt[i];


}




