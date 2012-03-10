/* Compile-time polymorphism using templates




  
  "Take a look at Exceptional C++ Style: 
  40 New Engineering Puzzles, Programming
  Problems, and Solutions", by Herb Sutter

  See Item 5 in the book.
*/
#include <iostream>
using namespace std;
class A{
 public:
  void x( int a=0)
  { cout << "A.x " << a << endl; }
  void y( int a=0)
  { cout << "A.y " << a << endl; }
};

class B{
public:
  void x(int a=0, double b=5.0)
  {
    cout << "B.x a,b:" << a << " " << b << endl;
  }

  void y(int a=0, double b=5.0)
  {
    cout << "B.y a,b:" << a << " " << b << endl;
  }
};

template<typename T>
void h(T& t) {
  t.x();
  t.y();
}

int main(void)
{
  A p;
  B q;

  h(p);
  h(q);
}

