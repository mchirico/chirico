#!/usr/bin/env python
def f(n):
   return n*n

k=sum([f(i) for i in xrange(0,100000)])
print k
