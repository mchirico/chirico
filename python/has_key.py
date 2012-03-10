#!/usr/bin/env python
"""
  Demonstrates .has_key and .get

"""

h={'mike':45,'susan':44,'lisa':44}
if h.has_key('mike'):
    print h['mike']
    # Now remove it
    del h['mike']



username = h.get('mike','unkown user')
print username

