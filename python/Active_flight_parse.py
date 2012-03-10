#!/usr/bin/env python
"""
  This script compares counts.

  You can run this as follows:
      scp tflms01:/tmp/active_flight_cnt .;./Active_flight_parse.py


"""


import sys, re
p = re.compile('ACTIVE: ([0-9][0-9]*)[ ]*GHOSTING ([0-9][0-9]*)')
d = re.compile('([A-Z|a-z]{3}) ([A-Z|a-z]{3})  ([0-9])+ ([0-9][0-9])\:([0-9][0-9])\:([0-9][0-9])')
dsort = re.compile('([0-9][0-9]+)\/([0-9][0-9]*)\/([0-9]*) ([0-9][0-9])\:([0-9][0-9])\:([0-9][0-9])')

month=['Jan','Fed','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec']

def pr(n):
    z=['faatc','toca','moca']
    if (n >= 0):
         return z[n]
    else:
         return len(z)


def stats(n):
    count=0
    k={}
    print "moca,toca,delta,datetime"
    for i in n.keys():
        if i == '':
            continue
        moca=0
        toca=0
        for j in n[i]:
            if ('moca' in j):
                 moca= j[0]
            if ('toca' in j):
                 toca= j[0]
#            print j,i
            count= count +1
            
        m=dsort.search(i)
        if m:
            k[m.group(3)+m.group(1)+m.group(2)+m.group(4)+m.group(5)+m.group(6)]=str(moca)+","+str(toca)+","+str(int(moca-toca))+","+str(i)
    keys=k.keys()
    keys.sort()
    for i in keys:
            print k[i]


            
f=open('active_flight_cnt')
r=f.readlines()
f.close()
j=0
last_date=''
z=[]
h={}
for i in r:
    m=d.search(i)
    if m:
# This is a date fix for Excel        
        last_date=str(month.index(m.group(2))+1)+'/'+m.group(3)+'/'+'2009'+' '+m.group(4)+':'+m.group(5)+':'+m.group(6)
    m=p.search(i)
    if m:
#       print m.group(1) +','+m.group(2)+','+pr(j%pr(-1))+','+str(last_date)
       z.append([int(m.group(1)),int(m.group(2)),pr(j%3),int(j%3),str(last_date)])
       if (str(last_date) in h):
           
           h[str(last_date)].append( [int(m.group(1)), int(m.group(2)),pr(j%pr(-1))] )
       else:
           h[str(last_date)]= [ [int(m.group(1)), int(m.group(2)),pr(j%pr(-1))]]
       j=j+1

stats(h)


       

       

