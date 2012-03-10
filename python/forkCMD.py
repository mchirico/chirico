#!/usr/bin/env python

import os,sys,re,time


def forkCMD(A):
    if len(A) <= 0:
        return
    pid = os.fork()
    if pid:
        print "parent:"+str(A)+" waiting for child"
        forkCMD(A[1::]) 
        cpid=os.waitpid(0,0)
        print "Parent sees child "+str(cpid)+ " is done"
    else:
        print "child:"+str(A[0])+" childpid: "+str(os.getpid())
        p=os.popen(A[0])
        m=p.readlines()
        p.close()
        print m
        print "child:"+str(A[0])+" childpid: "+str(os.getpid())+" is done"
        sys.exit(0)
        


#
# 
#
if __name__ == '__main__':
    b=['df','date','uptime']
    forkCMD(b)
