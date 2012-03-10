#!/usr/bin/env python

import pickle

d=dict(age=21,sex='M',id='23-23',card='Active')
f=open('data.pkl','wb')
pickle.dump(d,f)
f.close()
# It is now dumped

f=open('data.pkl','rb')
d2=pickle.load(f)
f.close()

print d2


