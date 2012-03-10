#!/usr/bin/env python

import sys, re

pat = re.compile('http://([A-Z|a-z]*\.([A-Z|a-z|0-9]*\.)*(org|com|gov)).*.')
while 1:
    line = raw_input('Enter a line ("q" to quit):')
    if line == 'q':
        break
    mo = pat.search(line)
    if mo:
        value = mo.group(1)
        print 'value: %s' % value
    else:
        print 'no match'
