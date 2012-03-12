#!/usr/bin/env python
"""


"""
import os,time,sys,signal,getopt,popen2,re

f=open("port_list")
m=f.readlines()
f.close()
m = [i.strip() for i in m]
m= [i.split() for i in m]

# This will find everything
h={}
for i in m:
    p=os.popen("port info %s|grep 'Homepage'" % i[0])
    s = p.readlines()
    p.close()
    if len(s) >= 1:
         s=s[0]
    if isinstance(s,str) and s.find('github') != -1:
       print s
       h[i[0]]=s




