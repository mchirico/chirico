#!/usr/bin/env python

import os,sys
def f(n):
    if n.find('cwxstat') == -1:
        return 0
    else:
        return 1




if __name__ == '__main__':
    r=os.popen('ps -auxf').read().split('\n')
    print filter(f,r)


