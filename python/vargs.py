#!/usr/bin/env python
def myvarargs(first, *arguments, **keywords):
    for arg in arguments: print arg
    keys = keywords.keys()
    keys.sort()
    for kw in keys: print kw, ':', keywords[kw]

myvarargs('first','one','two','thee',a='This is a', b='This is b')


