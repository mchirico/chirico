#!/usr/bin/env python
"""


"""
import os,time,sys,signal,re,random


pat = re.compile('[0-9][0-9]:[0-9][0-9]:[0-9][0-9] ')

def signal_handler(signal, frame):
        sys.exit(0)


def mcmd():
	f=os.popen('sar 1 2')
	m=f.readlines()
	f.close()
	return m

def mclean(n):
	a=[]
	count=0
	for i in n:
		mo = pat.search(i)
		if mo:
			a.append(str(count)+" 0 "+i.strip('\n'))
			count=count+1;
	return a

		




def Tabit(n):
	
	m=n.split(" ");
	t=""
	s=""
	while('' in m):
		m.remove('')
	for i in m:
		s=s+t+i
		t="\t"
	return s


def main(N):
	print Tabit("-1 0 one two three four five")
	m=mclean(mcmd())
	
	for i in m:
		print Tabit(i)



def mrandom(n):
	s=""
	s=s+n
	for i in range(1,10):
		s=s+" "+str(random.randint(0,100))
	return s

def mainT(N):
	print Tabit("-1 0 One Two Three Four Five Six Seven Eight Nine Ten")
	for i in range(0,30):
		print Tabit(mrandom(str(i)+" "+str(random.randint(0,1))+" "+str(i) ) )
	for i in range(60,100):
		print Tabit(mrandom(str(i)+" "+str(random.randint(0,1))+" "+str(i) ) )







if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        mainT(sys.argv)
