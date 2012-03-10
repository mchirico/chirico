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
        count=8 # Only wait 8 seconds
        print "parent:"+str(A)+" waiting for child"
        forkCMD(A[1::]) 
        print "parent: pid= ",pid," os.wait() =",os.waitpid(pid,os.WNOHANG)
        cpid=0
        try:
            cpid=os.waitpid(pid,os.WNOHANG)
            while(cpid[1] == 0):
                count = count-1
                if count <= 0:
                    print "The following is taking too long ", A[0]
                    count=20
                    time.sleep(6)
                    #break 
                time.sleep(1)
                print "parent: pid= ",pid," os.wait() =",os.waitpid(pid,os.WNOHANG)
                cpid=os.waitpid(pid,os.WNOHANG)
        except:
            print "HERE  ",pid
        finally:
            if count > 0:
                READ(pid)
            else:
                os.kill(pid,9)  # Kill 9 if doesn't return after count seconds
                print "Was killed because it took too long: ",A[0]
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
    b=['sleep 5','sleep 1','sleep 30','sleep 30','ssh 192.168.1.2']
    forkCMD(b)
    print H
#
# 
#
if __name__ == '__main__':
    main()
    
    
