/* Copyright (C) 2007 GPL  Mike Chirico mmc mchirico@users.sourceforge.net

  This is an example of the Strategy Design Pattern.

  Problem:

      Some ducks quack, squeek, or make no noise. For example,
      rubber ducks squeek, and decoy ducks don't make any noise.

      Given that there may be lots of different kinds of ducks, each
      making no sounds or different sounds, the Strategy Design Pattern
      can help with code reuse.

  Again, change is a constant in code. The Strategy Design Pattern helps with
  code reuse by make parts (noise that a duck makes) interchangeable.


*/


#include <iostream>


class QuackBehavior {
public:
  QuackBehavior(){}
  virtual ~QuackBehavior(){}
  virtual void quack() {  }
};


class Squeek: public QuackBehavior {
public:
  Squeek(){}
  void quack() { std::cout << "  squeek" << std::endl; }
};


class Quack: public QuackBehavior {
public:
  void quack() { std::cout << "  Quack " << std::endl; }
  ~Quack() {}
};


class Mute: public QuackBehavior {
public:
  void quack() { std::cout << "  <<silence>>" << std::endl; }
};


class Duck {
public:
  Duck(int i=1) { put_i(i);}
  virtual ~Duck() {
                std::cout << "Deleted Duck" << std::endl; 
                 }
  void put_i(int i) { 
    if( i > 0 )
      _i = i;
    else
      _i = -i;
  }
  int get_i() { return _i; }

   virtual void noise() { 
     for(int i=0; i<_i; ++i)
          quackBehavior->quack();
   }
   void set_quack(QuackBehavior *qb) { 
           quackBehavior = qb; 
   }
private:
  int _i;
  QuackBehavior *quackBehavior;
};


class Mallard: public Duck {
public:
  Mallard(int i=1): Duck(i), quackBehavior(new Quack()) { 
              set_quack(quackBehavior); 
               }
  ~Mallard() { 
    delete quackBehavior;
           std::cout << "Deleted Mallard" << std::endl; 
        }
private:
  QuackBehavior *quackBehavior;
};



class RubberDuck: public Duck {
public:
  RubberDuck(int i=1): Duck(i), quackBehavior(new Mute()) { 
              set_quack(quackBehavior); 
               }
  ~RubberDuck() { 
    delete quackBehavior;
           std::cout << "Deleted RubberDuck" << std::endl; 
        }
private:
  QuackBehavior *quackBehavior;
};



class DecoyDuck: public Duck {
public:
  DecoyDuck(int i=1): Duck(i), quackBehavior(new Squeek()) { 
              set_quack(quackBehavior); 
               }
  ~DecoyDuck() { 
    delete quackBehavior;
           std::cout << "Deleted DecoyDuck" << std::endl; 
        }
private:
  QuackBehavior *quackBehavior;
};



int main(void)
{
  Duck *duck = new Mallard(3);
  duck->noise();
  delete duck;

  duck = new RubberDuck(2);
  duck->noise();
  delete duck;

  duck = new DecoyDuck();
  duck->noise();
  delete duck;


}
