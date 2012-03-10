#!/usr/bin/env python
import urllib
import urllib2
from weather import *


url='http://weather.cwxstat.org/post'
req = urllib2.Request(url)
r = urllib2.urlopen(req)
lastWeather = str(r.read())

a=weather(lastWeather)

url='http://weather.cwxstat.org/post'
values={'Temp':'71.2','Hum':'41','Time':'3:23','Notes':'null'}
values['List']=str(a)
data = urllib.urlencode(values)
req = urllib2.Request(url,data)
r = urllib2.urlopen(req)
a = r.read()
print a
