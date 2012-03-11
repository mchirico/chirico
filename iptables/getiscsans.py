#!/usr/bin/env python
import os,sys,re

def getUpdate():
   f=os.popen('wget http://isc.sans.org/ipsascii.html?limit=10000 -O isc.sans.org')


def readList():
   f=open('isc.sans.org','r')
   k=f.readlines()
   f.close()
   return k


def buildList(n):
    p=re.compile('[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*')
    a={}
    for i in n:
       m=p.search(i)
       if m:
          s=m.group()
          s=s.replace('.0','.')
          if s[0] == '0':
             s=s[1::]
          if s[0:7] not in ['192.168','127.0','10.0']:
             a[s+'.0/24']=0
    s=''
    for i in a:
      s=s+ "-A INPUT -p tcp -s %s --dport 22 -j DROP\n" % i
    return s

getUpdate()
s=buildList(readList())
f=open('iscrules','w')
f.write(s)
f.close()

