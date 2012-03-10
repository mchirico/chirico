#!/usr/bin/env python

import os,sys


if __name__ == '__main__':
    r=os.popen2('cat /proc/uptime','t')
    k=r[1].readlines()[0].split()
    print k


