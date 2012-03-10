#ifndef ISTREAMEXAMPLE_H
#define ISTREAMEXAMPLE_H
#include <iostream>
#include <string>

class IstreamExample {
 public:
 IstreamExample():sum(0),i(0) {}
  IstreamExample(std::istream &is) { is >> *this; }
  friend std::istream& operator>>(std::istream&, IstreamExample&);
  friend std::ostream& operator<<(std::ostream&, const IstreamExample&);
  unsigned get_sum() { return sum; }
 private:
  std::string s;
  unsigned sum;
  int i;
};

using std::istream; using std::ostream;

inline
istream&
operator>>(istream& in, IstreamExample& istreamExample)
{
  std::cout << "Enter <string> <number>" << std::endl << std::endl;
  in >> istreamExample.s >> istreamExample.i;
  // check that the inputs succeeded
  if (in) {
    std::cout << "s =  " << istreamExample.s << " i = " << istreamExample.i << std::endl;
    istreamExample.sum+=istreamExample.i;
    std::cout << "sum = " << istreamExample.get_sum() <<  std::endl <<
      "To Exit enter: stop stop" << std::endl;
  }
  else
    istreamExample = IstreamExample();  // input failed: reset object to default state
  return in;
}
#endif
