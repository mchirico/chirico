/*
  Simple example to demonstrate assignment of variables
  in a class.

     - i is assigned in the form i(ii)
     - sE=5 is not possible because "explicit SimpleE.."

  Note,  C++ can be found in the following download:
  http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

*/
#include <iostream>

class Simple {
private:
  int i;
public:
  Simple(int ii): i(ii) { std::cout << "i has been assigned in constructor base initializer, Simple(int ii): i(ii) " << i << std::endl; }
  Simple& put_i(int ii)
      { 
      i=ii; //only constructors take base initializers. That's why no : i(ii) like above
      std::cout << "put_i. i is " << i << std::endl;
      return *this;
      }

};

class SimpleE {
private:
  int i;
public:
  explicit SimpleE(int ii): i(ii) { std::cout << "i has been assigned " << i << std::endl; }
  SimpleE& put_i(int ii)
      { 
	i=ii; //only constructors take base initializers. That's why no : i(ii) like above
      std::cout << "put_i. i is " << i << std::endl;
      return *this;
      }
};





int main()
{
  Simple s(3);
  SimpleE sE(12);
  
  
  s=5;
  // sE=5; //cannot do this because it's explicit

  s.put_i(12);
  sE.put_i(12);

  return 0;

}
