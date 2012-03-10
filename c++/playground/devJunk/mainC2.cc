#include <iostream>

class Mix {
public:
    Mix(int i=4):a(i) {
        std::cerr << "mix created" << std::endl;
    }

    virtual int  run() {
        std::cerr << "Mix run " << a  << std::endl;
        return 0;
    }
    virtual ~Mix() {
        std::cerr << "Mix deleted" << std::endl;
    }

private:
    int a;

};


class Mix2:public Mix {

public:
  Mix2(int i=78):a(i) { std::cerr << "Mix2 created" << std::endl;}
  ~Mix2() { std::cerr << "Mix2 deleted" << std::endl;}
  int run() { std::cerr << "Mix 2 " << std::endl; }
private:
  int a;
};




class A {
public:
    A(int i=0):a(i),mix(0){
        std::cerr << "A(int i=0):" << a << std::endl;
    }
    // You need to make this virtual or B's constructor
    // will not be called.
    virtual ~A() {
        delete mix;
        std::cerr << "~A()" << std::endl;
    }

    void assignMix(Mix *m) {
      if ( mix != 0 )
	delete mix;
      mix=m;
    }
    int runMix(){
        return mix->run();
    }

  Mix *getMix() { return mix; }

private:
    int a;
    Mix *mix;
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
    a->assignMix(new Mix2(34));
    a->runMix();
    delete a;


    a=new A();
    delete a;

    return 0;
}
