#!/usr/bin/env python
"""


"""
import os,time,sys,signal,re,gzip


def signal_handler(signal, frame):
        sys.exit(0)


def readMiddlegz(n):
	f=gzip.open(n,'rb')
	f.seek(-1)
	f.seek(f.tell()/2)
	m=f.read(40)
	f.close()
	return m
	



def main(N):
    print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
