/* Copyright (C) 2007 GPL  Mike Chirico mmc mchirico@users.sourceforge.net

  State Design Pattern

  Object:

     Several objects need to share a common state.

*/


#include <iostream>

class State
{
public:
  State(int state=0): _state(state),count_changes(0) {}
  void set_state(int state){
    _state=state;
    count_changes++;
  }
  void inc(){
    _state++;
    count_changes++;
  }
  int get_state() {
    std::cout << "state = " << _state << std::endl;
    return _state;
  }
  int num_state_changes(){
    std::cout << "Number State Changes = " << count_changes << std::endl;
    return count_changes;
  }
private:
  int _state;
  int count_changes;
};


class Obj_base
{
public:
  Obj_base() {}
  virtual ~Obj_base() {}

  State& state()
  {
    static State _state;
    return _state;
  }
};


class Obj_0: public Obj_base {
};

class Obj_1: public Obj_base {
};

class Obj_2: public Obj_base {
};





int main(void)
{

  Obj_0 object_zero;
  Obj_1 object_one;
  Obj_2 object_two;

  object_zero.state().set_state(3);
  object_one.state().get_state();
  object_two.state().inc();

  object_one.state().get_state();
  object_one.state().num_state_changes();

  return 0;
  

}
