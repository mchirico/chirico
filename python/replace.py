#!/usr/bin/env python
#  This is an example of removing all the leading
#  zeros from a string.

import re

s="08 1204 09 02 00"
s=re.sub(' 0([0-9])',' \g<1>',s)
s=re.sub('0([0-9])','\g<1>',s)

print s
