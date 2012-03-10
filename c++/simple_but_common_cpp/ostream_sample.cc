/* Copyright (c) 2007 GPL mchirico@users.sourceforge.net

  This is a simple example of using printing out private
  class members using ostream.

  ostream should be a friend of the class to access members.


*/

#include <iostream>
#include <string>

using namespace std;

class A {
  friend ostream& operator<<
    (ostream& out, const A& a);
  friend ostream& operator<<
    (ostream& out, const A *a);
public:
  A(int x=5, int y=5):x_(x),y_(y){}
  
  
private:
  int x_;
  int y_;
};

ostream& operator<<(ostream& out, const A& a)
{
  cout << "(" << a.x_ << "," << a.y_ << ")" << endl;
  return (out);
}

ostream& operator<<(ostream& out, const A *a)
{
  cout << "Using a-> (" << a->x_ << "," << a->y_ << ")" << endl;
  return (out);
}

int main(void)
{

  A a(5);
  A *b = new A(34);

  cout << a;
  cout << b;

  delete b;
}
