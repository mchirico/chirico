#!/usr/bin/env python
"""
  Note do not use 

       map(string.atoi(), a.split())   # Bad atoi()

  Instead

       map(string.atoi(), a.split())   # Good atoi, no ()

"""

import string
a='1 2 3 4 5 6'
p=map(string.atoi,a.split())
print p

