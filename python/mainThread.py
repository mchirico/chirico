#!/usr/bin/env python
#  Created by Mike Chirico 
#
"""
  
What happens if one thread gets stuck. This is
going to be a problem with the thread.join.



"""
import threading,os,time,sys,signal,getopt,subprocess
from time import sleep, ctime
# Globals
H={}


#threadLock = threading.Lock()
#
#  Use this if you need synchronous
#     threadLock.acquire()
#            ....stuff to do
#     threadLock.release()




# In threaded mode this does something different.
# Ctl-c will catch and exit
def signal_handler(signal, frame):
    print "You entered a signal"
    sys.exit(0)

# Runs ssh command
def runcmd(N,threadID,len=0):
    scmd=N
    w,r,e = os.popen3(scmd)
    H[threadID]=[r.readlines(),e.readlines()]
#    l=w.readlines()
    r.close()
    e.close()
    w.close()


def threadFUNC(nloop, CMD,threadID):
    runcmd(CMD,threadID,len=0)


# Order that this goes in.
#    1. Build
#    2. Start
#    3. Run
#  Now, if you want to run this again, you just
#  do threadRun
#Break this into sections
#  a. build
#  b. run
def threadBuild(loops):
    print 'starting at:', ctime()
    threads=[]
    nloops=range(len(loops))
    for i in nloops:
        t = threading.Thread(target=threadFUNC, args=(i, loops[i],i))
        threads.append(t)
    return threads



def threadStart(nloops,threads):
    for i in nloops:
        threads[i].start()


def threadJoin(nloops,threads):
    for i in nloops:
        threads[i].join()


def threadRun(nloops,threads):
    for i in nloops:
        threads[i].run()



def threadPrint():
    for i in H.keys():
        print H[i][0]



def threadLoop(loops):
    print 'starting at:', ctime()

    threads=threadBuild(loops)
    nloops=range(len(loops))
    threadStart(nloops,threads)
    # Is this python verion specific?
    print threading.activeCount()
    threadJoin(nloops,threads)

    print "all Done at:", ctime()
    threadPrint()
    return [loops,threads]


def threadLoopAgain(loops,threads):
    nloops=range(len(loops))
    print "*****************************"
    sleep(3)

    print "****** Running again ******"
    
    threadRun(nloops,threads)
    threadJoin(nloops,threads)
    threadPrint()




"""
Use this option to login
 ssh -q -o ConnectTimeout=1 -o NumberOfPasswordPrompts=0  <server>

 Note, if you don't get logged in, you'll execute the command on the
 computer this is run on.

"""
def buildList(server,cmd,A=[]):
    A.append("""ssh -q -o ConnectTimeout=1 -o ConnectTimeout=2 -o NumberOfPasswordPrompts=0   %s 'hostname -s;source ~/.bash_profile;%s' 2>/dev/null""" % (server,cmd))
    return A



def main(nargs):
    loops = buildList("mAW","ls")
    loops = buildList("mS","ls",loops)
    [l,t]=threadLoop(loops)
    sleep(2)
    [l,t]=threadLoop(loops)
#  No. For some reason I cannot do this.
#    threadLoopAgain(l,t)
#    threadLoopAgain(l,t)



if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main(sys.argv)    
       
        




