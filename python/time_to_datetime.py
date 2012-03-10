#!/usr/bin/env python
"""


"""
import os,time,sys,signal,datetime


def signal_handler(signal, frame):
        sys.exit(0)


def main(N):
	t0=time.strptime('05/12/11 18:47:34','%m/%d/%y %H:%M:%S')
	t1=time.strptime('05/31/11 11:48:34','%m/%d/%y %H:%M:%S')
	a=datetime.datetime.fromtimestamp(time.mktime(t0))
	b=datetime.datetime.fromtimestamp(time.mktime(t1))
	print "Differences in seconds:",(b-a).seconds
	print "Differences in days:",(b-a).days

    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
