#include <iostream>
/* The following example is taken from Item 23 in Meyers.
   But, I disagree that const should be taken for the
   operator*, since this prevents conversion to this,
   making it impossible to get .dec() or .p()

*/


class R {
public:
  R(int numerator =0,
           int denominator =1):n(numerator),d(denominator){};

  double dec(){ return static_cast<double>(n)/static_cast<double>(d); }

  void p() { std::cout << (double)n/(double)d << std::endl; }

friend
   R operator*(const R& lhs,const R& rhs)
  {
    return R(lhs.n * rhs.n, lhs.d * rhs.d);
  }

private:
  int n, d;
};
int main(void)
{
  R r(4,5),r2(1,2);
  std::cout << r.dec() << std::endl;
  std::cout << (r*r).dec() << std::endl;
  std::cout << (3*r*3).dec() << std::endl;

  (r*r2*r).p();

  
}
