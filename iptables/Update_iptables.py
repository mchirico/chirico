#!/usr/bin/env python
#
# http://chirico.googlecode.com/svn/trunk/iptables/Update_iptables.py
#
# cron
#  15 0 * * * /root/bin/Update_iptables.py >/dev/null 2>&1
import os,sys,re

def etc():
    h={}
    h['svn']='/root/dev/chirico/iptables/'
    h['iptables']='/root/dev/chirico/iptables/iptables'
    return h

def getiptables():
    f=os.popen('/sbin/iptables-save')
    m=f.readlines()
    f.close()
    return m

def write(n,m):
    f=open(m,'w')
    [f.write(i) for i in n]
    f.close()

def svnupdate(n):
    s="/usr/bin/svn commit "+n+" -m 'Auto commit from cron job'"
    f=os.popen(s)
    m=f.readlines()
    f.close()
    return m


m=getiptables()
if len(m) != 0:
   h=etc()
   write(m,h['iptables'])
   svnupdate(h['svn'])




