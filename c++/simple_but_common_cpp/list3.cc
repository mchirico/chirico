/* Copyright (c) GPL mchirico@users.sourceforge.net

   Example if list using sort on a class
   with user defined comparison "cmp_t".


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
#include <cmath>



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

public:
  cmp_t(int ii=0): i(ii) {}

  bool operator() (const  t&,const  t& y) const;
};

bool cmp_t::operator() (const t& x,const  t& y) const 
{

  switch(i) {
  case 0:
    return x.get_i() < y.get_i();
    break;
  case 1:
    return x.get_j() < y.get_j();
    break;
  case 2:
    return x.get_i() < y.get_j();
    break;
  case 3:
    return x.get_j() < y.get_i();
    break;
  case 4:
    return  ( x.get_i()-x.get_j() ) < ( y.get_i()-y.get_j() ) ;
    break;
  case 5:
    return  ( x.get_j()-x.get_i() ) < ( y.get_j()-y.get_i() ) ;
    break;
  case 6:
    return  ( sqrt(pow((double)x.get_i(),2) - pow((double)y.get_j(),2) ) <  sqrt( pow((double)y.get_i(),2) - pow((double)y.get_j(),2) )) ;
    break;
  default:
    return x.get_i() < y.get_i();
  }


}

ostream& operator<<(ostream&s, const t& tt)
{
  return s << '(' << tt.get_i() << ',' << tt.get_j() << ')';
}



int main(void)
{

  list<t> lst;
  t ta[5];


  ta[0].set_i(1);
  ta[0].set_j(2);

  ta[1].set_i(2);
  ta[1].set_j(1);

  ta[2].set_i(3);
  ta[2].set_j(8);

  ta[3].set_i(4);
  ta[3].set_j(7);

  ta[4].set_i(-3);
  ta[4].set_j(7);


  lst.push_back(ta[0]);
  lst.push_back(ta[1]);
  lst.push_back(ta[2]);
  lst.push_back(ta[3]);
  lst.push_back(ta[4]);

  lst.sort(cmp_t(0));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(1));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(2));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(3));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(4));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(5));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

  lst.sort(cmp_t(6));
  copy(lst.begin(),lst.end(),ostream_iterator<t>(cout," "));
  cout << endl << endl;

}




