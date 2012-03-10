#!/usr/bin/env python
import sys,os;
r=os.popen('ls').read().split('\n')
print "There are %d files in this directory\n" % (len(r)-1)
for i in r:
    print i



""" 

   You could also do the following:

   for line in os.popen('ls -l').readlines():
       print line[:-1]

"""
print "\n The following is all in one for loop:\n"
for line in os.popen('ls -l').readlines():
       print line[:-1]


"""

   Now for the quickest way:

"""

print "\n Just one command os.listdir:\n"
print os.listdir('.')


