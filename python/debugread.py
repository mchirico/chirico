#!/usr/bin/env python
"""

os.listdir('.')
Also see glob
http://oreilly.com/catalog/lpython/chapter/ch09.html

faa_ss_5_B8_1BK-OPSCORE_R5KSAT_debug_performance.log
"""
import os,time,sys,signal,datetime,glob
dateformat="%m %b %Y %H:%M:%S"
sample="01 Jun 2011 21:36:42"
sample2="01 Jun 2011 21:36:43"


def parseline(n):
	try:
		t,id = n[0].split(",")
		t=time.strptime(t,dateformat)
		a=n[1].split()
		h={}
		for i in a:
			key,value=i.split('=')
			h[key]=value
		key,value=n[2].split()
		h[key]=value
		mdelay={}
		mdelay[n[-2].strip()]= int(n[-1].strip())
		return [t,h,mdelay]
	except:
		return []
		


def readlog():
	file=glob.glob('*_debug_performance.log')
	f=open(file[0])
	m=f.readlines()
	f.close()
	m2=[i.split('###') for i in m]
	del(m)
	return m2
	



def signal_handler(signal, frame):
        sys.exit(0)


def main(N):
	t0=time.strptime(sample,dateformat)
	t1=time.strptime(sample2,dateformat)
	a=datetime.datetime.fromtimestamp(time.mktime(t0))
	b=datetime.datetime.fromtimestamp(time.mktime(t1))
	print "Differences in seconds:",(b-a).seconds
	print "Differences in days:",(b-a).days

    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
