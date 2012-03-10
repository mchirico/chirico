#!/usr/bin/env python
import threading
from time import sleep, ctime

loops = (5,4,3,2)

class MyThread(threading.Thread):
    def __init__(self, func, args, name=''):
        threading.Thread.__init__(self)
        self.name=name
        self.func=func
        self.args=args

    def run(self):
        print "In run(self):<start>"
        apply(self.func, self.args)
        print "In run(self):<end>"



def loop(nloop, nsec):
    print 'start loop', nloop, 'at:', ctime(), ' nsec=',nsec
    sleep(nsec)
    print 'loop', nloop, 'done at:', ctime()

def main():
    print 'starting at:', ctime()
    threads=[]
    nloops=range(len(loops))

    for i in nloops:
        t = MyThread(loop, (i, loops[i]),
                         loop.__name__)
        threads.append(t)

    for i in nloops:
        threads.append(t)

    for i in nloops:
        threads[i].start()

    for i in nloops:
        print "start join"
        threads[i].join()
        print "end join"

    print 'all DONE at:', ctime()

if __name__ == '__main__':
    main()
