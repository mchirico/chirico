#!/usr/bin/env python
"""




"""

import Queue
import threading
import urllib2
import time
import os,sys


def buildCMD(server,cmd):
    return """ssh -q -o ConnectTimeout=1 -o ConnectTimeout=2 -o NumberOfPasswordPrompts=0   %s 'hostname -s;source ~/.bash_profile;%s' 2>/dev/null""" % (server,cmd)    

#scmds = ["ssh mAW 'ls -l'","ssh mS  'hostname'"]

scmds = [buildCMD("mAQ","ls -l"),buildCMD("mS","hostname"),buildCMD("mS","date")]

queue = Queue.Queue()
out_queue = Queue.Queue()

def runcmd(N,len=0):
  scmd=N
  w,r,e=os.popen3(scmd)
  result=[r.readlines(),e.readlines()]
  r.close()
  e.close()
  w.close()
  return result




class ThreadUrl(threading.Thread):
    """Threaded Url Grab"""
    def __init__(self, queue, out_queue):
        threading.Thread.__init__(self)
        self.queue = queue
        self.out_queue = out_queue

    def run(self):
        while True:
            #grabs host from queue
            scmd = self.queue.get()

            #grabs urls of scmds and then grabs chunk of webpage
            r = runcmd(scmd)
            chunk = r[0]

            #place chunk into out queue
            self.out_queue.put(chunk)

            #signals to queue job is done
            self.queue.task_done()

class DatamineThread(threading.Thread):
    """Threaded Url Grab"""
    def __init__(self, out_queue):
        threading.Thread.__init__(self)
        self.out_queue = out_queue

    def run(self):
        while True:
            #grabs scmds from queue
            chunk = self.out_queue.get()

            #parse the chunk
            print chunk


            #signals to queue job is done
            self.out_queue.task_done()

start = time.time()
def main(argv):

    #spawn a pool of threads, and pass them queue instance
    for i in range(5):
        t = ThreadUrl(queue, out_queue)
        t.setDaemon(True)
        t.start()

    #populate queue with data
    for s in scmds:
        queue.put(s)

    for i in range(5):
        dt = DatamineThread(out_queue)
        dt.setDaemon(True)
        dt.start()


    #wait on the queue until everything has been processed
    queue.join()
    out_queue.join()


if __name__ == '__main__':
#    signal.signal(signal.SIGINT, signal_handler)
    main(sys.argv)    
    print "Elapsed Time: %s" % (time.time() - start)

