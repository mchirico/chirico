#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>


using namespace std;

class A {

public:

  A(const char *cc):c(cc) {}
  void pr() { std::cerr << "pr()=" << c << std::endl; }
  ~A() { std::cerr << c << std::endl; }

private:
  const char *c;

};


int main(void)
{
  vector<A*> v1;
  vector<A*> v2;


  v1.push_back(new A("One"));
  v1.push_back(new A("Two"));

  v1.front()->pr();
  
  // This is not exception safe, but it will do the job
  for(vector<A*>::iterator iter = v1.begin(); iter != v1.end(); ++iter)
    delete *iter;

  v1.reserve(30);
  cout << "calling v1.reserve(30) " << endl;
  cout << "v1.capacity()= " << v1.capacity() << endl;
  cout << "v1.size()= " << v1.size() << endl;



  v1.clear();
  return 0;
}
