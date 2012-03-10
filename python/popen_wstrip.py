#!/usr/bin/env python
"""
  This program strips out all the \n.

  Note len(k) will give the number of files returned.

  You could also do:

     r=os.popen("ls").read().split()

  This way there would be no need for k.


  Or, you could do something like this

     k=[i.replace('\n','') for i in os.popen('ls').readlines()]


"""



import os,sys


if __name__ == '__main__':
    r=os.popen2("ls")
    k=map(lambda x: x.rstrip(), r[1].readlines())
    print k



