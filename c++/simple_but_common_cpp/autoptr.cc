/* A very simple program to demonstrate auto_ptr.

   Note with auto_ptr there is not need to call delete.
   There are disadvantages, like pointers cannot be copied
   without returning a null value.

*/

#include <memory>
#include <cstdlib>
#include <cstdio>


class B {
 public:
  B(int _s): s(_s) { fprintf(stderr, "B was created\n");}
  ~B() { fprintf(stderr,"There goes B with value %d\n",s); }
 private:
	int s;
};

int main(void)
{


  {
  std::auto_ptr<B> b(new B(3));
  }
  fprintf(stderr, "That was it...B is now out of scope\n");


  return 0;

}
