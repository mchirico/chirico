/*  
    Example of passing *this in a simple class, which
    always has this format: 



    F&  function() { ...
                         return *this;

                        }


*/

#include <iostream>

class B {

public:

  B(int a=0): a_(a) { fprintf(stderr, "created a_=%d\n",a_);}
  ~B() { fprintf(stderr, "destroyed a_=%d\n",a_);}

   B& p(int a) {
    a_=a; 
    fprintf(stderr,"a_ = %d\n",a_);
    return *this; 
  }

   B& p() {
    fprintf(stderr,"a_ = %d\n",a_);
    return *this; 
  }

  B& operator()() {
    a_++;
    return *this; 
  }

private:

  int a_;
};

int main(void)
{
  B *b = new B(3);
  b->p();
  b->p(1).p(2).p(3).p(4);
  (*b)();  /* This increments a_ */
  delete b;

}
