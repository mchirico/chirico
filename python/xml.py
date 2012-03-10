#!/usr/bin/env python
import os, time

def mreader(FILE):
    f=open(FILE)
    m=f.readlines()
    f.close()
    return m


def getmeat(n,TAG):
    s=n
    try:
        while (type(s).__name__ == 'list'):
           s=s[0]
        s=s.lstrip().replace('<'+TAG+'>','')
        s=s.rstrip().replace('</'+TAG+'>','')
    except:
        return ''
    finally:
        return s



def extract_tag(n,TAG,STOPAT=35):
    count=-1
    flag=0
    s=[]
    k=[]
    for i in n:
       if (count >= STOPAT):
           count=-1
	   k=[]
       if (i.find('<'+TAG+'>') >= 0):
           count=0
       if (count >= 0):
          k.append(i)
          count=count+1
       if (i.find('</'+TAG+'>') >= 0):
           flag=1
           s.append(k)
           k=[]
           count=-1
    return s






if __name__ == '__main__':
    m=mreader('log.xml')
    s=extract_tag(m,'MESSAGE')
    for i in s:
        k=getmeat(extract_tag(i,'MSG_TEXT'),'MSG_TEXT')
        p=getmeat(extract_tag(i,'TSTZ_ORIGINATING'),'TSTZ_ORIGINATING')
        print p,k
