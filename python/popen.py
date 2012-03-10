#!/usr/bin/env python

import os,sys


if __name__ == '__main__':
    r=os.popen('cat /proc/uptime').read().split()
    print r


