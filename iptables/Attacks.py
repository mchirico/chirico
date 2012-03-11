#!/usr/bin/env python
#
# http://chirico.googlecode.com/svn/trunk/iptables/Attacks.py
#
# cron
#  */5 * * * * /root/bin/Attacks.py >/dev/null 2>&1
import os,sys,re,datetime

MAIL="/bin/mail -s 'Attack on computer big' mchirico@gmail.com"


def mail(n):
    s='\''+str(n).replace('\'','')+'\''
    p=os.popen("echo "+s+"|"+str(MAIL))
    p.close()

def ifmailbuild(a):
    if a == []:
       return
    s="\n\n"
    for i in a:
       s=s+i+'\n'
    if len(s) >= 5:
       mail(s)



def log(n):
    f=open('/var/log/attack','a')
    f.write(datetime.datetime.now().strftime("%Y.%m.%d (%A) %H:%M:%S")+": ")
    f.write(str(n))
    f.write('\n')
    f.close()

def ips(n):
    p=re.compile('[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*\.[0-9][0-9]*')
    h={}
    for i in n:
         m=p.search(i)
         if m:
             if m.group() in h:
                h[m.group()]=h[m.group()]+1
             else:
                h[m.group()]=1
    return h

def getpast():
    a=[]
    p=re.compile('-A INPUT -s ([0-9][0-9]*\.[0-9][0-9]*\.)[0-9][0-9]*\.[0-9][0-9]*(/[0-9][0-9]*)* -p tcp -m tcp --dport 22 -j DROP')
    f=os.popen('/sbin/iptables-save','r')
    d=f.readlines()
    f.close()
    for i in d:
        m=p.search(i)
        if m:
           if int(m.group(2)[1::]) <= 16:
             a.append(m.group(1))
    return a


def myexec(n):
    p=re.compile('^/sbin/iptables -I')
    m=p.search(n)
    if m:
       print "executing:",n
       f=os.popen(n)
       f.close()


def rules(n):
    p=re.compile('[0-9][0-9]*\.[0-9][0-9]*\.')
    a=[]
    a2=[]
# White list
    w=['192.168.','10.0.','127.0']
    past=getpast()
    for i in n:
         m=p.search(i)
         if m:
            s="-A INPUT -p tcp -s %s --dport 22 -j DROP" % (m.group()+'0.0/16')
            s2="/sbin/iptables -I  INPUT -p tcp -s %s --dport 22 -j DROP" % (m.group()+'0.0/16')
            if m.group() not in w:
              a.append(s)
              if m.group() not in past:
                a2.append(s2)
    return a2
    


if __name__ == "__main__":
    r=os.popen("grep 'Failed password for invalid user' /var/log/secure")
    m=r.readlines()
    r.close()
    h=ips(m)
    a=rules(h)

    for i in a:
       myexec(i)
       log(i)

    ifmailbuild(a)





