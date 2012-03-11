#!/usr/bin/env python

import re,os


def runAttacks(n):
    p=os.popen('/root/bin/AttacksAudit.py')
    p.close()


def getip(n):
   p=re.compile('([0-9][0-9]*\.[0-9][0-9]*\.)[0-9][0-9]*\.[0-9][0-9]*(/[0-9][0-9]*)*')
   m=p.search(n)
   if m:
      print m.group(1)
      runAttacks(m.group(1))



from socket import *
myHost = ''   
myPort = 10000

sockobj = socket(AF_INET, SOCK_STREAM)   
sockobj.bind((myHost, myPort))           
sockobj.listen(50)                            # listen, allow 50 pending connects





while True:                                    # listen until process killed
    connection, address = sockobj.accept( )   # wait for next client connect
    print 'Server connected by', address       # connection is a new socket
    while True:
        data = connection.recv(1024)         # read next line on client socket
        print "got data",data
        getip(data)
        if not data: break                   # send a reply line to the client
    connection.close( )




