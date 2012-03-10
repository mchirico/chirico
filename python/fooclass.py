#!/usr/bin/env python
"""


"""
import os,time,sys,signal

class Foo:
	@staticmethod
	def add(x,y):
		return x+y



def signal_handler(signal, frame):
        sys.exit(0)






def main(N):
	print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
	if len(sys.argv) > 1:
		print sys.argv
    
		
	print "Foo.add(2,2)=%s" % (Foo.add(2,2))

if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
