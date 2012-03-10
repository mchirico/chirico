#!/usr/bin/env python
import sys,os;
"""
Add the following to crontab:

# NTP monitor
0,10,20,30,40,50 * * * * /root/bin/check_ntp.py >/dev/null 2>&1

"""


k=os.popen('/etc/init.d/ntpd status').read().find('running')
if k < 0:
  r=os.popen('/etc/init.d/ntpd restart').read().split()
  print r
  r=os.popen('rdate -s time-b.nist.gov').read().split()
  print r
else:
  print "ntp running"








