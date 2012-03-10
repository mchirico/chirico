#include <iostream>

class B {
public:
  explicit B(int x = 0, double y=3):x_(x),y_(y) {}
  // B(int x = 0, double y=3):x_(x),y_(y) {}

  int get_x() { return x_; }
  double get_y() { return y_; }
private:
  int x_;
  double y_;
};


void doSomething(B bObject){
  std::cout << "In doSomething: " <<  bObject.get_x() << ", " << bObject.get_y() << std::endl;
}


int main(void)
{
  doSomething(B(3,9.2));
  //doSomething(9); // This works without explicit
}
