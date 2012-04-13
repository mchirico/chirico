#!/usr/bin/env python
#  Created by Mike Chirico 
#
"""



"""
import mythread,signal,sys
import ConfigParser
from time import sleep, ctime
from datetime import date

CONFIG_FILE="gateCheck.config"
Config = ConfigParser.ConfigParser()


today=date.today()
datestamp=today.strftime("%y%m%d")

# In threaded mode this does something different.
# Ctl-c will catch and exit
def signal_handler(signal, frame):
    print "You entered a signal"
    sys.exit(0)




# Load config
# CONFIG_FILE="gateCheck.config"
"""
Config.get('remove_filters','cmd')

"""
def loadConfig():
    Config.read(CONFIG_FILE)
    
        

def pr(q):
    while not q.empty():
        for i in q.get()[0]:
             print i.strip()

#
# Returns a list
#    buildQlist(q,[]) if you don_t want to append
def buildQlist(q,a=[]):
    while not q.empty():
        a.append(q.get()[0])
    return a
            

#

def buildcmd(x,servers,cmd_string,loops=[]):
    for i in servers:
        loops = x.buildList(i,cmd_string,loops)
    return loops

def buildcmdQ(x,servers,cmd_string,loops=[]):
    for i in servers:
        loops = x.buildListQ(i,cmd_string,loops)
    return loops




# pr(genCmd())
def genCmd(S):
    x=mythread.DoThread()
    exec("servers="+Config.get('servers','servers'))
    loops=buildcmdQ(x,servers,Config.get(S,'cmd'),[])
    [l,t]=x.threadLoop(loops)
    q=x.get_s()
    return x.get_s()



def main(nargs):
    loadConfig()
    pr(genCmd('test'))
    pr(genCmd('test2'))


if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main(sys.argv)    
       
        
