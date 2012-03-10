#!/usr/bin/env python

def p(x,l=[]):
     for i in x:
             if isinstance(i,list):
                  p(i)
             else:
                  print i

# Reference:
# http://mail.python.org/pipermail/tutor/2001-January/002914.html
def flatten(L):
    if type(L) != type([]): return [L]
    if L == []: return L
    return flatten(L[0]) + flatten(L[1:])
