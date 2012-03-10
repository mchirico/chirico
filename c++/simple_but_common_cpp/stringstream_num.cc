/* Copyright (c) GPL mchirico@users.sourceforge.net

   This class works with stringstream to convert numbers
   in a string to double and run simple stats on these
   numbers.



*/




#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


class A {

public:

  A(const string & s): s_(s) {
    stringstream ss(s);
    double val;
    while ( ss >> val)
      {
	sum_+=val;
        v.push_back(val);
      }
     count=v.size();
   }


 void  recal(const string & s) {
    stringstream ss(s);
    double val;
    v.clear();
    sum_=0;
    while ( ss >> val)
      {
	sum_+=val;
        v.push_back(val);
      }
     count=v.size();
   }


  void ins(const string &s) {
    stringstream ss(s);
    double val;
    while(ss >> val)
      {
	sum_+=val;
        v.push_back(val);
      }

    count=v.size();
  }

 void  mod(int i=1) {

    int tcount=0;
    count=0;
    sum_=0;
    for(vector<double>::const_iterator iter(v.begin()); iter != v.end(); ++iter)
      {
	if(++tcount % i == 0)
          {
            sum_+= *iter;
            count++;
	  }
      }
  }


  string list(int i=1) {
    int tcount=0;
    string spacer="";
    stringstream ss("");
     for(vector<double>::const_iterator iter(v.begin()); iter != v.end(); ++iter)
       {
	 if(++tcount %i == 0)
	   {
             ss << spacer;
	     ss << *iter;
             spacer=" ";
           }
       }
     return ss.str();
  }

  double avg() {
    return sum_/count;
  }

  double sum() {
    return sum_;
  }

private:

  string s_;
  double sum_;
  vector<double> v;
  double count;

};


int main () {

  A a("1 2 3 4 5");

  cout << "avg: " << a.avg() << " sum: "<< a.sum() << endl;
  a.ins("6 7 8 9 10 11 12 13 14 15");
  cout << "avg: " << a.avg() << " sum: "<< a.sum() << endl;
  a.mod(3);
  cout << "avg: " << a.avg() << " sum: "<< a.sum() << endl;
  cout << a.list(5) << endl;


  a.recal("5 10 15");
  cout << "avg: " << a.avg() << " sum: "<< a.sum() << endl;
  return 0;
}
