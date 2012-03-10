#include <iostream>



class A {
public:
    A(int i=0):a(i){
        std::cerr << "A(int i=0):" << a << std::endl;
    }
  // You need to make this virtual or B's constructor
  // will not be called.
    virtual ~A() {
        std::cerr << "~A()" << std::endl;
    }

private:
    int a;

};

class B:public A {
public:
    B(int i=3):a(i) {
        std::cerr << "B(int i=0):" << a << std::endl;
    }
    ~B() {
        std::cerr << "~B()" << std::endl;
    }
private:
    int a;
};


int main(void)
{
    A *a=new B();
    delete a;

    a=new A();
    delete a;
    return 0;
}
