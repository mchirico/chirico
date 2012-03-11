#!/usr/bin/env python
"""
You can find a copy of this file at
http://chirico.googlecode.com/svn/trunk/bash/pingtest/summary.py


"""
import os,time,sys,signal,re


def signal_handler(signal, frame):
        sys.exit(0)


#
#
p=re.compile('\[([0-9]{10})\.')
#Destination Net Unreachable
SECONDS_DOWN=500

def getEpoch(N):
    if isinstance(N,list):
     if len(N) > 0:
       if isinstance(N[0],str):
          if N[0].find('Destination Net Unreachable') != -1:
		  return False
       	  m=p.search(N[0])
	  if m:
	     return m.group(1)
    return False
            


def dateConvert(epoc):
	s= """date -d "1970-01-01 %s sec UTC" """ % (epoc)
	p=os.popen(s)
	results=p.readlines()[0].strip()
	p.close()
	return results

	



def main(N):
	file='data'
	if len(sys.argv) > 1:
		file=sys.argv[1]
	f=open(file)
	m=f.readlines()
	f.close()
	m=[int(getEpoch(i.split())) for i in m]
	m=[ i for i in m if i != 0]

	delta=[]
	delta2=[]
	for i in range(0,len(m)-1,2):
		delta.append(m[i+1]-m[i])
		delta2.append([m[i+1]-m[i],m[i+1],m[i]])
	top = [ i for i in delta if i >= SECONDS_DOWN]
	mtimes = [ delta2[j][1::]  for j in [delta.index(i) for i in top]]
	h={}
	for i in mtimes:
		key=dateConvert(i[0])
		value=dateConvert(i[1])
		h[key]=[value,i[0]-i[1],i[0],i[1]]

        hks=h.keys()
	hks.sort()
	totMin=(m[-1]-m[0])/60
	s="\nReport Coverage (%3d min):%32s to %27s" % (totMin,dateConvert(m[0]),dateConvert(m[-1]))
	print s
	print 95*'-'
	s="%5s %s %3s %10s %26s %36s " % ('TSecs','/', 'Mins','Down From', 'Down To','(Epoch1,Epoch2)') 
	print s
	totDown=0
        for i in hks:
	     s="%5d %5d %30s %s (%s,%s) " % (h[i][1],h[i][1]/60,h[i][0],i,h[i][2],h[i][3])
	     totDown = totDown + h[i][1]/60
	     print s
	print "%5s %5s" % ('','------')
	print "%5s %5d  Percentage down: %3d%%" % ('',totDown,int(totDown/float(totMin)*100))


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)
