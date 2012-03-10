#!/usr/bin/env python
"""
   Created by Mike Chirico

"""
import os,re,time,sys,signal


def signal_handler(signal, frame):
        sys.exit(0)


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
        forkCMD(A[1::]) 
        cpid=os.waitpid(0,0)
        READ(cpid[0])
    else:
        p=os.popen(A[0])
        m=p.readlines()
        p.close()
        LOG(os.getpid(),m)
        sys.exit(0)
        


def buildcmds(N):
	a=[]
	for i in N:
		a.append("""ssh -t """+str(i)+""" "echo '"""+str(i)+"""'" 2>/dev/null""")
	return a



def downUp(servers,K):
	a=set([i[0].strip() for i in K.values() if len(i) != 0 ])
	b=set(servers)
	return [list(b.difference(a)),list(b.intersection(a))]


def main(n):
	servers=['squeel.org','cluster1','junk']
	forkCMD(buildcmds(servers))
	print "What is down:",downUp(servers,H)[0]
	print "What is up:",downUp(servers,H)[1]
    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
