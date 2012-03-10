#!/usr/bin/env python

# Reference Python: Essential Reference, Third Edition
# Also take a look at  m=[k.append(s) for s in open("class.py")]
#
#   svalues=['1','2','3']
#   [float(s) for s in svalues]
f=open("read.py")
line = f.readline()
while line:
    print line,
    line = f.readline() # Note ',' omits newline character
f.close()
    
