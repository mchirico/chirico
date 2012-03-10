#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <deque>
using namespace std;

template <typename T> class Sum {
  T res;
  long count;

public:
  Sum(T i=0,long j=0): res(i),count(j) { }
  void operator() (T x) {res +=x; count +=1;}
  T result() const { return res;}
  long num() const { return count;}
  double avg() const { return result()/(double) num();}
};



template <typename T, template <typename> class C>
void f(C<T> &ld)
{
  Sum<T> s;
  s=for_each(ld.begin(), ld.end(), s);
  cout << "the sum is " << s.result() << std::endl;
  cout << "number of elements " << s.num() << std::endl;
  cout << "avg " << s.avg() << std::endl;

}


int main(void)
{
  list<double> l;
  vector<int> v;
  deque<long> d;

  l.push_back(3.5);
  l.push_back(9.5);
  //f(l);   //Something wrong with g++ 4.3

  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  //f(v);    //Something wrong with g++ 4.3

  d.push_back(34000001);
  d.push_back(134512312);
  d.push_front(12123123);
  d.push_back(12123123);
  //f(d);  //Something wrong with g++ 4.3



}


