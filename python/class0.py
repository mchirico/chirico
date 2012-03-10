#!/usr/bin/env python

class Foo:
    def __init__(self, value):
        self.value = value
    def __add__(self, other):
        return Foo(self.value + other.value)


a = Foo(5)
b = Foo(2)
c = a+b
print c.value



