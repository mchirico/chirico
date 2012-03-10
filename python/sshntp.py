#!/usr/bin/env python
import os, time
from slib import *


def readlog(n,server):
    f=open(n,"r")
    s=f.readlines()
    f.close()
    x=[]
    for i in s:
        if (i[0] == "*"):
            x=i.strip('\n')
            j=x.split(' ')
            x=[i for i in j if i != '']
    x.append(server)
    return x


def docmd(usr,svr,passw,logr,log):
    s=S()
#    s.setuhpld('username','host','Pa33word','/tmp/log1ntp.1','log1.1')
    s.setuhpld(usr,svr,passw,logr,log)
    a=['/usr/sbin/ntpq -np']
    s.lcmd(a)
    return readlog(log,svr)

if __name__ == '__main__':
    m=docmd('username','host','Pa33word','/tmp/log1ntp.1','log1.1')
    print m


"""
     remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
*10.245.172.100  10.245.172.102   2 u  473 1024  377    0.288   -0.371   0.523
+10.245.172.101  10.245.172.103   2 u  248 1024  377    0.253    0.311   0.706
 127.127.1.0     73.78.73.84      5 l    7   64  377    0.000    0.000   0.001

 
"""

