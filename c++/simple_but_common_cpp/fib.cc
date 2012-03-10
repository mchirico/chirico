#include <iostream>
#include <cstdlib>
using namespace std;
class Fib {
public:
  Fib() : a0_(0), a1_(1), count_(0) {}
  int operator()();
  int count();
private:
  int a0_, a1_, count_;
};
int Fib::operator()() {
  int temp = a0_;
  a0_ = a1_ ;
  a1_ = temp + a0_;
  count_++;
  return temp;
}
int Fib::count() {
  return count_;
}

int main(int argc, char **argv)
{
  Fib fib;

  int count=5;

  if (argc == 2) {
    count=atoi(argv[1]);
  }
  
  for(int i=0; i < count; ++i)
    {
      cout << fib() << endl;
    }



}
