#!/usr/bin/env python


def setDict(**keywords):
    return keywords


def stuff(**keywords):
    keys = keywords.keys()
    keys.sort()
    for i in keys: print i, ':', keywords[i]


def upgrade(**keywords):
     if keywords['Education'] == 'BA':
         print "\nneed to upgrade"
         keywords['Education']='MA'
     return keywords






stuff(name='Anderson', Age=45, Education='BA')



r=setDict(name='Anderson', Age=45, Education='BA')
print "\n\nsetDict(name='Anderson', Age=45, Education='BA') : ", r
r=upgrade(**r)
stuff(**r)






