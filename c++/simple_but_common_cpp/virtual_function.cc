/* Copyright (c) 2005 Mike Chirico mchirico@comcast.net mchirico@users.sourceforge.net
   

    Example of using virtual functions. Note the use of "initialization lists"
            for assigning the variable first and last.

    Compile:
      g++ -o virtualfunc -Wall -W -O2 -s -pipe  virtual_function.cc

    Download:
      http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download


*/

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <functional>


using namespace std;

class Employee {
  string first,last;
public:
  Employee(const string& fn="John",const  string& ln="Smith"): first(fn),last(ln) {}
  virtual void print() const {
  cout << "First name: " << first << ", Last name: " << last << endl;
  }
  virtual ~Employee() {}
};

class Manager : public Employee {
  int level;
  list<Employee*> subordinates;
public:
  Manager(const string& fn="Ivan",const string& ln="Stedwick", int lvl=1): Employee(fn,ln), level(lvl) {}
  void print() {
    cout << "Manager level: " << level << "  ";
    Employee::print();
    cout << "Supervises:" << endl;
    for_each(subordinates.begin(),subordinates.end(),mem_fun(&Employee::print));
    cout << endl << endl;
  }
  void addstaff(Employee& staff){
    subordinates.push_front(&staff);
  }
  void addstaff(Employee* staff){
    subordinates.push_front(staff);
  }

};


int main()
{
  Employee p0("Lisa","Payne");
  Manager m0;

  m0.addstaff(new Employee("Zoe","Bear")); /* uses void addstaff(Employee* staff) */
  m0.addstaff(new Employee("Leah","Bopper"));
  m0.addstaff(new Employee("Abby","Chicken"));
  m0.addstaff(p0);  /* void addstaff(Employee& staff)  needed for this one */
  m0.addstaff(new Employee());
  m0.print();
  

  return 0;
}
