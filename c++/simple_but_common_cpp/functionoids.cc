/*
   http://www.parashift.com/c++-faq-lite/pointers-to-members.html#faq-33.9












*/




#include <iostream>
#include <vector>
#include <string>

class Funct {
public:
  virtual int doit(int x) = 0;

  virtual ~Funct(){};
}; 


class Funct1 : public Funct {
public:
  Funct1(float y) : y_(y) { }
  virtual int doit(int x) {  std::cout << "this is func1" << x << y_ << std::endl;  return 0; }


private:
  float y_;
};
 
class Funct2 : public Funct {
public:
  Funct2(const std::string& y, int z) : y_(y), z_(z) { }
  virtual int doit(int x) { std::cout << "this is func2" << x << y_ << z_ << std::endl; return 0; }
private:
  std::string y_;
  int z_;
};
 
class Funct3 : public Funct {
public:
  Funct3(const std::vector<double>& y) : y_(y) {  }
  virtual int doit(int x) { std::cout << "this is func3" << x <<   std::endl; 
                            y_.push_back(x*3.5);
                            return 0; }
private:
  std::vector<double> y_;
}; 



typedef Funct* FunctPtr;

int main(void)
{
  FunctPtr array[10];




  array[0] = new Funct1(3.14f);
 
  array[1] = new Funct1(2.18f);
 
  std::vector<double> bottlesOfBeerOnTheWall;
  bottlesOfBeerOnTheWall.push_back(100);
  bottlesOfBeerOnTheWall.push_back(99);

    bottlesOfBeerOnTheWall.push_back(1);
    array[2] = new Funct3(bottlesOfBeerOnTheWall);
 
    array[3] = new Funct2("my string", 42);
 


  return 0;
}
