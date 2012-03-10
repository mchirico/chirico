#!/usr/bin/env python
import urllib
import urllib2
from weather import *


url='http://weather.cwxstat.org/rainpost'
req = urllib2.Request(url)
r = urllib2.urlopen(req)
lastWeather = str(r.read())

a=rain(lastWeather)


url='http://weather.cwxstat.org/rainpost'
values={}
values['List']=str(a)
data = urllib.urlencode(values)
req = urllib2.Request(url,data)
r = urllib2.urlopen(req)
a = r.read()
print a
