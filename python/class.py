#!/usr/bin/env python
# Simple example of creating a class with a default constructor
#
class C1():
    def __init__(self,who='joe'):
        self.name = who

    def setname(self, who):
        self.name = who

c1 = C1()
c1.setname('bob')
c2 = C1('sue')
c3 = C1()
print c1.name
print c2.name
print c3.name


