#include <iostream>
/* The following example is taken from Item 23 in Meyers.
   But, I disagree that const should be taken for the
   operator*, since this prevents conversion to this,
   making it impossible to get .dec() or .p()

*/

template <typename T>
class R {
public:
  R(const T& numerator =0,
           const T& denominator =1):n(numerator),d(denominator){};


  double dec(){ return static_cast<double>(n)/static_cast<double>(d); }

  void p() { std::cout << (double)n/(double)d << std::endl; }

friend
   R<T> operator*(const R<T>& lhs,const R<T>& rhs)
  {
    return R<T>(lhs.n * rhs.n, lhs.d * rhs.d);
  }

private:
  T n, d;
};



int main(void)
{
  R<double> r(4.7,5),r2(1.0,2.2);
  std::cout << r.dec() << std::endl;
  std::cout << (r*r).dec() << std::endl;
  std::cout << (3.1*r*3).dec() << std::endl;

  (r*r2*r).p();

  
}
