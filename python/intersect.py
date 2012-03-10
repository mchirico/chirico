#!/usr/bin/env python
def intersect(s1,s2):
    res = []
    for x in s1:
      if x in s2:
         res.append(x)
    return res

k = (1,2,4,5)
p = (5,3,5)
print intersect(k,p)

k = "note"
p = "boat"
print intersect(k,p)


