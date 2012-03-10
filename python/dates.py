#!/usr/bin/env python
#
import datetime
t = datetime.date.today()
print t.strftime('%A, %d-%b-%Y')


import calendar
lastFriday = datetime.date.today()
while lastFriday.weekday() != calendar.FRIDAY:
    lastFriday -= datetime.date.resolution
print "Last Friday was: " + lastFriday.strftime('%A, %d-%b-%Y')

#
#  This method below does not need looping
#
friday = calendar.FRIDAY
thisDay = t.weekday()
deltaT = (thisDay - friday) % 7
lastFriday2 = t - datetime.timedelta(days=deltaT)
print "\n\nLast Friday was: " + lastFriday2.strftime('%A, %d-%b-%Y')







