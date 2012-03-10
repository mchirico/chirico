#!/usr/bin/env python
def lfig(n):
      k=[]
      if not isinstance(n,list):
            return k
      for i in n:
            if isinstance(i,list):
                  k.append(1)
            else:
                  k.append(0)
      return k

n=[1,2,4,[1,3,[3,4]],3,[2,1],5]
print lfig(n)






    
