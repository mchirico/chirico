#!/usr/bin/env python

#  a+  Open for reading and writing 
#      create if does not exist, otherwise create
#  r+  Open for reading and writing. Must exist
#  w+  Open for reading and writing, but smash the old stuff
#
f=open('junk.txt','a+')
f.seek(0,2)
f.write('This is a sample of junk\n\n')
f.seek(0)
f.read()
f.write('more data \n\n');
f.seek(0,2) # this brings you to the end
f.write('last stuff')
f.seek(0)
print f.read()
f.close()
