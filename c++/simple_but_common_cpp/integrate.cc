/* This example taken from Item 18
   of "C++ Common Knowledge" by Stephen C. Dewhurst.

   Note virtual declaration "virtual ~Func() {}"
*/

#include <iostream>
using namespace std;

class Func {
public:
  virtual double operator()(double)=0;
  virtual  ~Func(){}
};

class NMFunc:public Func {
public:
  NMFunc( double(*f)(double)): f_(f) {}
  double operator()(double d) { return f_(d);}
private:
  double (*f_)(double);
};

double integrate( Func &f, double low, double high, int numsteps) {
  double step = (high-low)/numsteps;
  double area = 0.0;
  while(low<high) {
    area += f(low)*step;
    low += step;
  }
  return area;
}

double aFunc(double x) {
  return 2*x+5;
}

int main(void)
{
  NMFunc g(aFunc);
  double area = integrate(g, 0.0, 5, 2000);
  cout << "Area of 2*x+5 [0,5]=" << area << endl;
  return 0;
}
