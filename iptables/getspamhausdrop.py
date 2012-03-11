#!/usr/bin/env python
import os,sys,re

def getUpdate():
   f=os.popen('rm -f ./drop.lasso')
   f=os.popen('wget http://www.spamhaus.org/drop/drop.lasso')


def readList():
   f=open('drop.lasso','r')
   k=f.readlines()
   f.close()
   return k


def buildList(n):
    p=re.compile('[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*/[0-9][0-9]*')
    a=[]
    for i in n:
       m=p.search(i)
       if m:
          a.append(m.group())
    s=''
    for i in a:
      s=s+ "-A INPUT -p tcp -s %s --dport 22 -j DROP\n" % i
    return s

getUpdate()
s=buildList(readList())
f=open('spamhausrules','w')
f.write(s)
f.close()

