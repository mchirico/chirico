/*  Named Constructor Idiom.
    Reference: http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.6

*/
#include <iostream>
#include <cmath>
using namespace std;

class Point {

public:
  static Point rectangular(float x, float y);
  static Point polar(float radius, float angle);
  float get_x() { return x_; }
  float get_y() { return y_; }

private:
  Point(float x, float y);
  float x_, y_;
};

inline Point::Point(float x, float y)
  : x_(x), y_(y) {}

inline Point Point::rectangular(float x, float y)
{ return Point(x,y); }

inline Point Point::polar(float radius, float angle)
{ return Point(radius*cos(angle),radius*sin(angle)); }

int main(void)
{
  Point p1 = Point::rectangular(5.7,1.2);
  Point p2 = Point::polar(5.7,1.2);

  cout << "(" << p1.get_x() << ", " << p1.get_y() << ")" << endl;
  cout << "(" << p2.get_x() << ", " << p2.get_y() << ")" << endl;
}
