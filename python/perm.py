#!/usr/bin/env python
def perm(l):
         sz = len(l)
         if sz <= 1:
             return [l]
         return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]

print perm(['a','b','c'])


