#!/usr/bin/env python
#
class I(object):
    def f(self): pass
    def g(self): pass
 
class A(I):
    def f(self):
        print "A: doing f()"
 
    def g(self):
        print "A: doing g()"
 
class B(I):
    def f(self):
        print "B: doing f()"
 
    def g(self):
        print "B: doing g()"
 
class C(I):
    def __init__(self):
        # delegation
        self.i = A()
 
    def f(self):
        self.i.f()
 
    def g(self):
        self.i.g()
 
    # normal attributes
    def to_a(self):
        self.i = A()
 
    def to_b(self):
        self.i = B()
 
if __name__ == '__main__':
    c = C()
    c.f() # output: A: doing f()
    c.g() # output: A: doing g()
    c.to_b()
    c.f() # output: B: doing f()
    c.g() # output: B: doing g()

