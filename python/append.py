#!/usr/bin/env python
def f(a, L=[]):
    L.append(a)
    return L

def F(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L

for i in range(1,5):
    print f(i)

