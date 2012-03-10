#!/usr/bin/env python
#  Created by Mike Chirico  <mchirico2@csc.com>
#  Version 0.0.2
#      mmc (Tue Apr 28 17:17:37 GMT 2009)
#          Added logging with parameter
#
#  This script runs a command to see if the http service is alive.
#  If this service is not starting it sleeps for n seconds
#
#  Caution: This script does not use environment variables, since it
#       may not get passed the environment. If you change oracle 
#       versions, make sure this program can find opmnctl.
#
import os, sys, time, datetime

LOG="/tmp/checkhttp."

def grab_argv(n):
    try:
        if len(sys.argv) >= 1:
            if n in sys.argv:
                return LOG+sys.argv[sys.argv.index(n)+1]
    except:
        return LOG


def set_log():
    global LOG
    try:
    	LOG=grab_argv("-processType")+".log"
    except:
        LOG=LOG+".log"
    f=open(LOG,'w')
    f.close()


def log(n):
    f=open(LOG,'a')
    f.write(datetime.datetime.now().strftime("%Y.%m.%d (%A) %H:%M:%S")+": ")
    f.write(str(n))
    f.write('\n')
    f.close()



def pause(d=5):
    time.sleep(d)

def rcmd(cmd):
    p=os.popen(cmd,"r")
    a=p.readlines()
    p.close()
    return a


def ncmp(str0,str1):
    log(str0)
    try:
    	if (str0[0].strip() == str1):
		pause(2)  # Give it 2 secs
      		return False
    	else:
      		return True
    except:
         return True


if __name__ == '__main__':
    set_log()
    while(ncmp(rcmd('/opt/oracle/product/10.1.3.4/J2ee/opmn/bin/opmnctl status ias-component=HTTP_Server -noheaders -fmt %sta 2>&1'),'Alive')):
        print "Waiting HTTP_Server"
        log("Waiting HTTP_Server")
        pause()
    print "HTTP_Server Alive"
    log("HTTP_Server Alive")



