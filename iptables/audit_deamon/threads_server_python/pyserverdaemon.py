#!/usr/bin/env python

import re,os,sys,datetime
from socket import *

def runAttacks(n):
    p=os.popen('/root/bin/AttacksAudit.py')
    p.close()


def getip(n):
   p=re.compile('([0-9][0-9]*\.[0-9][0-9]*\.)[0-9][0-9]*\.[0-9][0-9]*(/[0-9][0-9]*)*')
   m=p.search(n)
   if m:
      runAttacks(m.group(1))
      log('running Attacks')

def log(n):
    f=open('/var/log/pyserverdaemon','a')
    f.write(datetime.datetime.now().strftime("%Y.%m.%d (%A) %H:%M:%S")+": ")
    f.write(str(n))
    f.write('\n')
    f.close()



def main():
   myHost = ''   
   myPort = 10000
   sockobj = socket(AF_INET, SOCK_STREAM)   
   sockobj.bind((myHost, myPort))           
   sockobj.listen(5)                            # listen, allow 50 pending connects
   while 1:
     connection, address = sockobj.accept( )   
     log(address)
     while True:
         data = connection.recv(1024)         # read next line on client socket
         if len(str(data)) > 2:
            log(data)
            getip(data)
         if not data: break                   # send a reply line to the client
     connection.close( )


if __name__ == "__main__":
     try:
       pid=os.fork()
       if pid > 0:
          sys.exit(0)
     except OSError, e:
       print >> sys.stderr, "fork #1 failed: %d (%s)" % (e.errno, e.strerror)
       sys.exit(1)
     os.chdir("/")
     os.setsid()
     os.umask(0)


     try:
       pid = os.fork()
       if pid > 0:
          print "Daemon PID %d" % pid
          sys.exit(0)
     except OSError, e:
       print >> sys.stderr, "fork #2 failed: %d (%s)" % (e.errno, e.strerror)
       sys.exit(1)
     main()





