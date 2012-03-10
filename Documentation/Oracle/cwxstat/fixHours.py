#!/usr/bin/env python
"""
  File to import records into Oracle

      

"""
import os
HOMEDIR=os.environ.get('HOME')

# User sql username and password
f=open(HOMEDIR+"/.oracle")
usrpass=f.read().split('/')
usrpass=[i.replace('\n','') for i in usrpass]
f.close()

# Load records
p=os.popen('sqlldr '+str(usrpass[0])+'/'+str(usrpass[1])+' control=Hours.ctl')
mout=p.readlines()
p.close()
for i in mout:
    print i,

#
p=os.popen('sqlplus '+str(usrpass[0])+'/'+str(usrpass[1])+' \@fix.sql')
mout=p.readlines()
p.close()

