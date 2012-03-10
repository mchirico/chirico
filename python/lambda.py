#!/usr/bin/env python
def times(n):
    return lambda x:x*n

def inc(n):
    return lambda x:x+n




a = times(5)
print a(0)
print a(1)
print a(2)


print "\n\n"

b = inc(5)
print b(0)
print b(1)
print b(2)


