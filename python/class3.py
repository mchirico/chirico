#!/usr/bin/env python
# Simple example of creating a class with a default constructor
#   Reference: http://www.cs.toronto.edu/~shiva/cscb07/lectures/pyobj.html
#              http://www.python.org/workshops/1997-10/proceedings/savikko.html


class A:
    def __init__(self,stat=2.718):
        self.stat= stat

    def myexec(self):
        return self.stat


class C1(A):
    def __init__(self,who='joe',a=A()):
        self.name = who
        A.__init__(self)
        self.a=a
        
    def setname(self, who):
        self.name = who
    
        


class C2(C1):
    def __init__(self,s='Default Stuff'):
        self.stuff = s
        C1.__init__(self)


    def setstuff(self, s=''):
        self.stuff=s


c1 = C1()
c1.setname('bob')
c2 = C1('sue')
c3 = C1()
c4 = C2()



print c1.name
print c2.name
print c3.name
print c4.name
print c4.stuff
print c4.myexec()



