#!/usr/bin/env python
#  Created by Mike Chirico 
#
"""
  
Quick class mythread for older version of
python


"""
import threading,os,time,sys,signal,getopt,popen2,Queue
from time import sleep, ctime

# In threaded mode this does something different.
# Ctl-c will catch and exit
def signal_handler(signal, frame):
    print "You entered a signal"
    sys.exit(0)

class DoThread(object):
    H={}
    queue = Queue.Queue()
# Give complete queue
    QUEUE=True
    s=object

    def set_s(self,S):
        self.s=S
    def get_s(self):
        return self.s
    
    def runcmd(self,N,threadID,len=0):
        scmd=N
        r,w,e = popen2.popen3(scmd)
        self.queue.put([r.readlines(),e.readlines()])
        r.close()
        e.close()
        w.close()

    def threadFUNC(self,nloop, CMD,threadID):
        self.runcmd(CMD,threadID,len=0)

    def threadBuild(self,loops):
        print 'starting at:', ctime()
        threads=[]
        nloops=range(len(loops))
        for i in nloops:
            t = threading.Thread(target=self.threadFUNC, args=(i, loops[i],i))
            threads.append(t)
        return threads

    def threadStart(self,nloops,threads):
        for i in nloops:
            threads[i].start()

    def threadJoin(self,nloops,threads):
        for i in nloops:
            threads[i].join()

    def threadRun(self,nloops,threads):
        for i in nloops:
            threads[i].run()

    def threadLoop(self,loops):
        print 'starting at:', ctime()
        threads=self.threadBuild(loops)
        nloops=range(len(loops))
        self.threadStart(nloops,threads)
        # Is this python verion specific?
        print threading.activeCount()
        self.threadJoin(nloops,threads)
        print "all Done at:", ctime()
        self.threadPrint()
        return [loops,threads]

    def threadLoopAgain(self,loops,threads):
        nloops=range(len(loops))
        print "*****************************"
        sleep(3)
        print "****** Running again ******"
        self.threadRun(nloops,threads)
        self.threadJoin(nloops,threads)
        self.threadPrint()

    def threadPrint(self):
        if self.QUEUE:
            self.set_s(self.queue)
            return 
        while not self.queue.empty():
            s=self.queue.get()[0]
            for i in s:
                print i.strip()

    def buildList(self,server,cmd,A=[]):
        A.append("""ssh -q -o ConnectTimeout=2 -o NumberOfPasswordPrompts=0   %s 'hostname -s;source ~/.bash_profile;%s' 2>/dev/null""" % (server,cmd))
        return A

