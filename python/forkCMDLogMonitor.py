#!/usr/bin/env python
"""
  This isn't finished.

"""


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



def STATUS():
    p=os.popen('ls -l .forklog.pid.*')
    m=p.readlines()
    p.close()
    print m



def forkMonitor(A):
    pid=os.fork()
    if pid:
        print "forkMonitor"
        cpid=0
        try:
            cpid=os.waitpid(pid,os.WNOHANG)
            while(cpid[1] == 0):
                time.sleep(1)
                STATUS()
                cpid=os.waitpid(pid,os.WNOHANG)
        except:
            print ""
    else:
        forkCMD(A)
        sys.exit(0)
        

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
    b=['df','date','uptime','seq 30','sleep 9','w']
    forkMonitor(b)
    print H
#
# 
#
if __name__ == '__main__':
    main()
    
    
