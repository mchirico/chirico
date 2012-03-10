#!/usr/bin/env python
"""
  Created by 

  Quick and dirty program to count 1521 (oracle established connections)

  TODO:

    


"""
import os,datetime,signal,sys,getopt,time

t=datetime.datetime.now().strftime("%Y.%m.%d.%A.%H.%M.%S")

def signal_handler(signal, frame):
    print "You entered a signal"
    sys.exit(0)



def Netstat():
    f=os.popen("""netstat  -nap|grep 1521|grep 'ESTABLISHED'|awk '{printf("%s\\n",$7)}'|sort|sed -e 's/\/java//g'|sed -e 's/\/oracledrcjmsi//g'|sed -e  's/\/oracleextptl1//g' |grep -v '-' 2>/dev/null""")
    m=f.readlines()
    f.close()
    m=[i.strip() for i in m]
    h={}
    for i in m:
      if h.has_key(i):
        h[i]=h[i]+1
      else:
        h[i]=1
    return h



def PrintToFile(FILE,s):
    print >> open(FILE,'w'), s

def PrintToStdout(s):
    print  s

def PrintToStdoutAndFile(FILE,s):
    print >> open(FILE,'w'), s
    print  s


def PrettyPrint(H):
    h=H
    sum=0
    err=0
    s=""
    s=s+ "\n%s\nPID\t #Connections\n" % (t)
    for i in h.keys():
      try:
         sum = sum + int(h[i])
      except Exception, e:
         err=err+1
      s=s+ "%s\t %s\n" % (i,h[i])
    s=s+ "__________________\n"
    s=s+ "total\t %s\n\n" % (sum)
    PrintToStdoutAndFile('/tmp/sumCount_conn',s)
    

def main(nargs):
    h=myparse()
    if h.has_key('-i'):
       while True:
    	 PrettyPrint(Netstat())
         time.sleep(6)
    else:
       PrettyPrint(Netstat())


def example_usage():
    print "The following options can be used with this program: "
    print "-h help -i infinite  "
    print  "Out also, always goes to /tmp/sumCount_conn "



def myparse():
    h={}
    opts=[]
    args=0
    try: opts,args=getopt.getopt(sys.argv[1:],'il:p:b:',
              ['file='])
    except Exception, e:
        example_usage()
        sys.exit(-1)
    if len(opts) == 0:
#        example_usage()
        return h
    for o, a in opts:
        h[o]=a

    return h




if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main(sys.argv)



