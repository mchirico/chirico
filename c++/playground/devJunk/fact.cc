#include "big_int.hpp"

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>


using namespace std;

void outputBigInt(BigInt<1024> x) {
  vector<int> v;
  if (x == 0) {
    cout << 0;
    return;
  }
  while (x > 0) {
    v.push_back((x % 10).toUlong( ));
    x /= 10;
  }
  copy(v.rbegin( ), v.rend( ), ostream_iterator<int>(cout, ""));
  cout << endl;
}

int main( ) {
  BigInt<1024> n(1);
  // compute 66 factorial
  for (int i=1; i <= 66; ++i) {
    n *= i;
  }
  outputBigInt(n);
}
