#!/usr/bin/env python
# 
# Sorting on the 2nd letter
def p(n):
    return n[2]


names=["Susan","bob","zoe","abby","tim","Ron"]


names.sort(key=lambda n: p(n))
print names

