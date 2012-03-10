def flatten(l):
    if isinstance(l,list):
        return sum(map(flatten,l))
    else:
        return l

"""
  This gives sum
"""

