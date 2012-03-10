#!/usr/bin/env python
"""


"""
import os,time,sys,signal,getopt,popen2,re



def signal_handler(signal, frame):
        sys.exit(0)


# Runs ssh command
def runcmd(N,len=0):
    scmd=N
    r,w,e = popen2.popen3(scmd)
    m=r.readlines()
    e.readlines()
    r.close()
    e.close()
    w.close()
    return [os.getpid(),m]
            







def forkCMD(A):
    if len(A) <= 0:
        return
    pid = os.fork()
    if pid:
	    forkCMD(A[1::])
	    cpid=os.waitpid(0,0)
	    print "done"
    else:
        eval(A[0])
        sys.exit(0)









def cpu1(N=100):
	a=range(1,5000)
	b=range(1,10000,2)
	c=[]
	for j in range(1,200):
	  for i in range(1,2000):
		c=a+a
		del(c)
		c=[]



def build(n=5):
	return [ 'cpu1()'  for i in range(1,n)]


def main(N):
#	print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
	if len(sys.argv) > 1:
		forkCMD(build(int(sys.argv[1])))

		


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)


