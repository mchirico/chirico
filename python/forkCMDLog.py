#!/usr/bin/env python

import os,sys,re,time

TMPFILE=".forklog.pid."+str(os.getpid())+'.'
H={}

def LOG(n,data):
    f=open(TMPFILE+str(n),'w')
    for i in data:
        f.write(i)
    f.close()


def READ(n):
    f=open(TMPFILE+str(n),'r')
    H[n]=f.readlines()
    f.close()
    os.unlink(TMPFILE+str(n))






def forkCMD(A):
    if len(A) <= 0:
        return
    pid = os.fork()
    if pid:
        print "parent:"+str(A)+" waiting for child"
        forkCMD(A[1::]) 
        cpid=os.waitpid(0,0)
        print "Parent sees child "+str(cpid)+ " is done"
        READ(cpid[0])
    else:
        print "child:"+str(A[0])+" childpid: "+str(os.getpid())
        p=os.popen(A[0])
        m=p.readlines()
        p.close()
        LOG(os.getpid(),m)
#        print m
        print "child:"+str(A[0])+" childpid: "+str(os.getpid())+" is done"
        sys.exit(0)
        


def main():
    b=['df','date','uptime','seq 30']
    forkCMD(b)
    print H
#
# 
#
if __name__ == '__main__':
    main()
    
    
