/* What is an explicit construction?

   This demonstrates the difference. Note 

       S s2 = 'a' 

   The above statement causes an error. It is an
   example of implicit conversion from char to int.

   When declaring a constructor explicit, this causes
   an ERROR. Try removing the explicit declaration below
   for a clearer understanding.

*/



#include <iostream>
using namespace std;

class S {
public:
  explicit S(int n): n_(n) {}
  //  S(int n): n_(n) {}
  int p() {
    return n_;
  }

private:
  int n_;
};

void f(S s) {

  cout << " " << s.p() << endl;
}

int main(void) {
  S s('a');
  //  S s2 = 'a';   //Error unless you take out explicit 
  f(S(3));
  //  f('a');      //Error unless you take out explicit 
}
