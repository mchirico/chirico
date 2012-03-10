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
            





def main(N):
	print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
	if len(sys.argv) > 1:
		print sys.argv



if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
#        main(sys.argv)
