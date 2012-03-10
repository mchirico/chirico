#!/usr/bin/env python
"""


"""
import os,time,sys,signal


def signal_handler(signal, frame):
        sys.exit(0)


def main(N):
	print "program "+sys.argv[0]+" called with "+str(len(sys.argv)) +" parameters"
	car = lambda lst: lst[0]
	cdr = lambda lst: lst[1:]


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
