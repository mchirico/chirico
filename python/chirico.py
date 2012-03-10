# These are common routines 
# that I use.
#
# from chirico import *
import os,sys

servers=["big2","root@soekris30","root@soekris10","cluster0","cluster1","squeezel","root@tape"]

def c(cmd):
    f=os.popen(cmd)
    return f.read().split('\n')

def cn(cmd):
    f=os.popen(cmd)
    return f.read()

def ssh(s,cmd):
    t="ssh %s -C %s" % (s,cmd)
    return cn(t)




def flat(L):
    if type(L) != type([]): return [L]
    if L == []: return L
    return flat(L[0]) + flat(L[1:])

    
