#!/usr/bin/env python
#  Created by Mike Chirico mchirico@gmail.com
#
import os,sys,re,time,signal

TMPFILE=".forkcmdclog.pid."+str(os.getpid())+'.'
H={}

# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)



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



def pp(H):
    keys = H.keys()
    keys.sort()
    for i in keys:
        try:
            print H[i][0].strip()+"  "+H[i][1].strip()
        except:
            print ""



def forkCMDc(A):
    if len(A) <= 0:
        return
    pid = os.fork()
    if pid:
#        print "parent:"+str(A)+" waiting for child"
        forkCMDc(A[1::]) 
        cpid=os.waitpid(0,0)
#        print "Parent sees child "+str(cpid)+ " is done"
        READ(cpid[0])
    else:
#        print "child:"+str(A[0])+" childpid: "+str(os.getpid())
        exec(A[0])
        LOG(os.getpid(),'0')
        sys.exit(0)



def stuff(a):
    a=a+1
    print a
    return a



def main():
    a=["""stuff(2)"""]
    a.append("""stuff(3)""")
    a.append("""print 'here'""")
    forkCMDc(a)

if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main()
