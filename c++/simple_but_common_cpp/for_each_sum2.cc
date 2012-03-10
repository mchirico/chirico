#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

template <typename T> class Sum {
  T res;
  long count;

public:
  Sum(T i=0,long j=0): res(i),count(j) { }
  void operator() (T x) {res +=x; count +=1;}
  T result() const { return res;}
  long num() const { return count;}
  double avg() const { return result()/num();}
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

  l.push_back(3.5);
  l.push_back(9.5);
  //f(l);   // Something wrong with g++ using template template

  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  // f(v); // Something wrong with g++ using template template


}


