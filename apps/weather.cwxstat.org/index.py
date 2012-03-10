import os
import thread
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import urlfetch
from google.appengine.ext.webapp.util import run_wsgi_app
import cgi
import wsgiref.handlers
import re
import string

# ************************************************************************
# ************************************************************************
#     Databases
# ************************************************************************
# ************************************************************************

class TempHum(db.Model):
  temp = db.StringProperty()
  hum = db.StringProperty()
  time = db.StringProperty()
  sensor = db.StringProperty()
  tag = db.StringProperty()
  notes =  db.StringProperty(multiline=True)
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

class Wind2(db.Model):
  direction = db.StringProperty()
  gust = db.StringProperty()
  avg = db.StringProperty()
  time = db.StringProperty()
  tag = db.StringProperty()
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

class Rain(db.Model):
  rate = db.StringProperty()
  tips = db.StringProperty()
  total = db.StringProperty()
  reset = db.StringProperty()
  time = db.StringProperty()
  timeEnter  = db.DateTimeProperty(auto_now_add=True)    

class hPa(db.Model):
  hpa = db.StringProperty()
  time = db.StringProperty()
  tag = db.StringProperty()
  timeEnter  = db.DateTimeProperty(auto_now_add=True)    

# ************************************************************************
# ************************************************************************


def mvavg(n,l):
  a=[]
  for i in range(0,len(n),l):
    a.append(sum(n[i:i+1])/l)
  return a

def stp(n):
  s=""
  d=""
  for i in n:
    s=s+d+str(int(string.atof(i)))
    d=","
  return s

def sstp(n):
  s=""
  d=""
  length=len(n)
  t=range(0,length)
  t=[i for i in t if i%(len(t)/5) == 0]
  t.reverse()
  for i in t:
    s=s+d+str(n[i])
    d="|"
  return s

def chartBubble(a,b,c):
  s="""
<img
  src="http://chart.apis.google.com/chart?cht=s&amp;chd=t:%s|%s|%s&amp;chxt=x,y&amp;chxl=0:|0|10|20|30|40|50|60|70|80|90|100|1:|0|20|40|60|80|100&amp;chs=800x250&amp;\
chco=0000ff,0000ff,000000&amp;chf=c,ls,0,EEEEFF,0.2,FFFFFF,0.2&amp;chg=10,20,1,4&chm=o,FF9900,0,4.0,15.0|h,000000,0,0.70,0.5|h,000000,0,0.32,0.5" alt="Scatter plot wi\
th default blue circle data points in different sizes as defined by a third data set" /><br />
   """%(stp(a),stp(b),stp(c))
  return s

def chartLXY(a,b,c,l):
  s="""
<img
  src="http://chart.apis.google.com/chart?cht=lxy&amp;
chd=t:%s|%s|%s|%s&amp;chxt=x,y&amp;chxl=0:|%s|1:|0|20|40|60|80|100|1:|0|10|20|30|40|50|60|70|80|90|100
&amp;chs=800x250&amp;\
chco=0000ff,00ff00,000000&amp;chf=c,ls,0,EEEEFF,0.1,FFFFFF,0.1&amp;chg=10,20,1,5
&chm=o,FF9900,0,4.0,15.0|h,000000,0,0.70,0.5|h,000000,0,0.32,0.5" alt="Scatter plot wi\
th default blue circle data points in different sizes as defined by a third data set" /><br />
   """%(stp(a),stp(b),stp(a),stp(c),sstp(l))
  return s







def graphRain():
    s=""
    r = db.GqlQuery("SELECT * FROM Rain ORDER BY timeEnter DESC LIMIT 200")
    a=[i.rate for i in r if int(i.rate) > 0]
    if len(a) >= 7:
      a=a[-7:]
      s="""
<img
  src="http://chart.apis.google.com/chart?cht=bvg&amp;chbh=5,2&amp;chbh=20&amp;chs=200x150&amp;chd=t:%s,%s,%s,%s,%s,%s,%s&amp;chco=76A4FB" alt="Bar c\
hart with line marker" /><br>Rain

"""%(a[0],a[1],a[2],a[3],a[4],a[5],a[6])
      return s


def graphWind():
    s=""
    r = db.GqlQuery("SELECT * FROM Wind2 ORDER BY timeEnter DESC LIMIT 7")
    a=[str(int(string.atof(i.avg))) for i in r]
    if len(a) >= 7:
      a=a[-7:]
      s="""<br>
<img
  src="http://chart.apis.google.com/chart?cht=bvg&amp;chbh=5,2&amp;chbh=20&amp;chs=200x150&amp;chd=t:%s,%s,%s,%s,%s,%s,%s&chds=0,30&amp;chco=76A4FB" alt="Bar c\
hart with line marker" /><br>Wind Avg

"""%(a[6],a[5],a[4],a[3],a[2],a[1],a[0])
      return s



def graphWindGust():
    s=""
    r = db.GqlQuery("SELECT * FROM Wind2 ORDER BY timeEnter DESC LIMIT 7")
    a=[str(int(string.atof(i.gust))) for i in r]
    if len(a) >= 7:
      a=a[-7:]
      s="""<br>
<img
  src="http://chart.apis.google.com/chart?cht=bvg&amp;chbh=5,2&amp;chbh=20&amp;chs=200x150&amp;chd=t:%s,%s,%s,%s,%s,%s,%s&chds=0,30&amp;chco=76A4FB" alt="Bar c\
hart with line marker" /><br>Wind Gust

"""%(a[6],a[5],a[4],a[3],a[2],a[1],a[0])
      return s


class T(webapp.RequestHandler):
  def get(self):
    self.response.out.write("<html><body>")
    self.response.out.write(graphRain())
    self.response.out.write("</body></html>")





class WindList(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM Wind2 ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time: '+str(i.time)+' Direction:'+str(i.direction)+' Gust:'+str(i.gust)+' Avg:' + str(i.avg)+'\n')

class TempList(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM TempHum where sensor='2' ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time: '+str(i.time)+' Temp:'+str(i.temp)+' Hum:'+str(i.hum)+'\n')

class TempListTest(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM TempHum where sensor='2' ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time: '+str(i.time)+' Temp:'+str(i.temp)+' Hum:'+str(i.hum)+'\n')



class RainList(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM Rain ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time:'+str(i.time)+' Rate:'+str(i.rate)+' Tips:'+str(i.tips)+' Total:' + str(i.total)+'\n')

class hPaList(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM hPa ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time:'+str(i.time)+' hpa:'+str(i.hpa)+'\n')




class List(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM TempHum where sensor='2' ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Time:'+str(i.time)+' Temp:'+str(i.temp)+' Hum:' + i.hum+'\n')



class RainPost(webapp.RequestHandler):
  def post(self):
    self.response.headers['Content-Type'] = 'text/plain'
    List=self.request.get('List')
    r = eval(List)

    for i in r:
      self.response.out.write('i[0]:'+str(i[0])+'\n')
      self.response.out.write('i[1]:'+str(i[1])+'\n')
      self.response.out.write('i[2]:'+str(i[2])+'\n')
      self.response.out.write('i[3]:'+str(i[3])+'\n')
      self.response.out.write('i[4]:'+str(i[4])+'\n')
      w0 = Rain(rate=str(i[0]),tips=str(i[1]),total=str(i[2]),reset=str(i[3]),time=str(i[4]),tag='Rain Test 0')
      w0.put()

  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM Rain ORDER BY timeEnter DESC LIMIT 1")
    for i in r:
      self.response.out.write(str(i.time))
    


class WindPost(webapp.RequestHandler):
  def post(self):
    self.response.headers['Content-Type'] = 'text/plain'

    List=self.request.get('List')
    r = eval(List)

    for i in r:
      self.response.out.write('i[0]:'+str(i[0])+'\n')
      self.response.out.write('i[1]:'+str(i[1])+'\n')
      self.response.out.write('i[2]:'+str(i[2])+'\n')
      self.response.out.write('i[3]:'+str(i[3])+'\n')
      
      w0 = Wind2(direction=str(i[0]),gust=str(i[1]),avg=str(i[2]),time=str(i[3]),tag='Wind Test 0')
      w0.put()


  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM Wind2 ORDER BY timeEnter DESC LIMIT 1")
    for i in r:
      self.response.out.write(str(i.time))


class hPaPost(webapp.RequestHandler):
  def post(self):
    self.response.headers['Content-Type'] = 'text/plain'
    List=self.request.get('List')
    r = eval(List)

    for i in r:
      self.response.out.write('i[0]:'+str(i[0])+'\n')
      self.response.out.write('i[1]:'+str(i[1])+'\n')
      w0 = hPa(hpa=str(i[0]),time=str(i[1]),tag='Test 0')
      w0.put()

  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM hPa ORDER BY timeEnter DESC LIMIT 1")
    for i in r:
      self.response.out.write(str(i.time))





class TestPost(webapp.RequestHandler):
  def post(self):
    self.response.headers['Content-Type'] = 'text/plain'


    Temp=self.request.get('Temp').rstrip()
    Hum=self.request.get('Hum').rstrip()
    Time=self.request.get('Time').rstrip()
    List=self.request.get('List')
    r = eval(List)



    for i in r:
      self.response.out.write('i[0]:'+str(i[0])+'\n')
      self.response.out.write('i[1]:'+str(i[1])+'\n')
      self.response.out.write('i[2]:'+str(i[2])+'\n')
      self.response.out.write('i[3]:'+str(i[3])+'\n')

      w0 = TempHum(temp=str(i[0]),hum=str(i[1]),sensor=str(i[2]),time=str(i[3]),tag='test2')
      w0.put()

    self.response.out.write('Temp:'+Temp+'\n')
    self.response.out.write('Hum:'+Hum+'\n')
    self.response.out.write('Time:'+Time+'\n')
    self.response.out.write('List:'+List+'\n')
    self.response.out.write('len(r):'+str(len(r))+'\n')


    
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    r = db.GqlQuery("SELECT * FROM TempHum ORDER BY timeEnter DESC LIMIT 1")
    for i in r:
      self.response.out.write(str(i.time))

    








class Ctest(webapp.RequestHandler):
  def get(self):
    r = db.GqlQuery("SELECT * FROM TempHum where sensor='2' ORDER BY timeEnter DESC LIMIT 1000")
    t=[]
    h=[]
    time=[]
    ttime=[]
    rows=0
    for i in r:
      if rows%50 == 0:
        t.append(i.temp)
        h.append(i.hum)
        time.append(i.timeEnter)
        ttime.append(i.time)
      rows=rows+1

    time.reverse()
    r = TempHum.all().filter('timeEnter < ',time[0]).filter('sensor = ','2').fetch(1000)
    time=[]

    for i in r:
      if rows%50 == 0:
        t.append(i.temp)
        h.append(i.hum)
        time.append(i.timeEnter)
        ttime.append(i.time)
      rows=rows+1

    time.reverse()
    r = TempHum.all().filter('timeEnter < ',time[0]).filter('sensor = ','2').fetch(1000)
    time=[]

    for i in r:
      if rows%50 == 0:
        t.append(i.temp)
        h.append(i.hum)
        time.append(i.timeEnter)
        ttime.append(i.time)
      rows=rows+1



    time.reverse()
    r = TempHum.all().filter('timeEnter < ',time[0]).filter('sensor = ','2').fetch(1000)
    time=[]

    for i in r:
      if rows%50 == 0:
        t.append(i.temp)
        h.append(i.hum)
        time.append(i.timeEnter)
        ttime.append(i.time)
      rows=rows+1


    time.reverse()
    r = TempHum.all().filter('timeEnter < ',time[0]).filter('sensor = ','2').fetch(1000)
    time=[]

    for i in r:
      if rows%50 == 0:
        t.append(i.temp)
        h.append(i.hum)
        time.append(i.timeEnter)
        ttime.append(i.time)
      rows=rows+1

        

    t.reverse()
    h.reverse()
    ttime
    l=ttime
#    l.reverse()

#    self.response.out.write(chartBubble(range(1,100),t,h))
    self.response.out.write(chartLXY(range(1,100),t,h,ttime))
    self.response.out.write("<br><br><br>")



    





class MainPage(webapp.RequestHandler):
  def get(self):
#    self.response.headers['Content-Type'] = 'text/plain'

    r = db.GqlQuery("SELECT * FROM TempHum where sensor='2' ORDER BY timeEnter DESC LIMIT 1000")
    s0=''
    s1=''
    s=''
    d=''
    c=90
    rows=0
    x=''

    for i in r:
      if rows%100 == 0:
        s0=s0+'Time: '+str(i.time)+' Temp: '+str(i.temp)+' Hum: ' + i.hum+'<br>'
        s=s+d+str(  int(string.atof(i.temp)))
        x=x+d+str(c)
        s1=s1+d+str(   int(string.atof(i.hum)) )
        d=','
        c=c-10
      rows=rows+1

    d=''
    s3=''
    rows=0
    r = db.GqlQuery("SELECT * FROM hPa ORDER BY timeEnter DESC LIMIT 1000")
    hpa_list=[]
    for i in r:
      if rows%100 == 0:
        s3= s3+d+str(i.hpa)
        hpa_list.append(int(i.hpa))
        d=','
      rows=rows+1


    hpa_list.reverse()
    t="""<a href=c><img src="http://chart.apis.google.com/chart?cht=lxy&amp;chs=200x125&amp;chd=t:%s|%s|%s|%s&amp;chco=3072F3,aa00ff,00ff33&amp;chls=1,1,1&amp;chm=s,FF0000,0,-1,5|c,0000ff,1,-1,5|c,00aa00,2,-1,5"
alt="Line chart with unevenly spaced data points and lines in red, green and dashed blue" /></a>
"""%(x,s,x,s1)

    t2="""<img src="http://chart.apis.google.com/chart?cht=lxy&amp;chs=200x125&amp;chd=t:%s|%s&chds=0,100,995,1030&amp;chco=3072F3,ff00ff,00ffaa&amp;chls=1,2,3&amp;chm=s,000f1,0,-1,5|s,ff000,1,-1,5|c,00aa00,2,-1,5"
alt="Line chart with unevenly spaced data points and lines in red, green and dashed blue" />
"""%(x,s3)




    self.response.out.write("<html><body>")
    self.response.out.write(t)
    self.response.out.write("<br>")
    self.response.out.write(t2)
    self.response.out.write("<br>")
    self.response.out.write(str(hpa_list) )
    self.response.out.write("<br>")
    self.response.out.write(s0)      
    self.response.out.write(graphRain())      
    self.response.out.write(graphWindGust())
    self.response.out.write(graphWind())    
    self.response.out.write("<br>Total rows:"+str(rows))
    self.response.out.write("</body></html>")

application = webapp.WSGIApplication(
                                     [('/', MainPage),
                                      ('/post',TestPost),
                                      ('/windpost',WindPost),
                                      ('/rainpost',RainPost),
                                      ('/hpapost',hPaPost),
                                      ('/list',List),
                                      ('/wind',WindList),
                                      ('/rain',RainList),
                                      ('/hpa',hPaList),
                                      ('/temp',TempList),
                                      ('/test',TempListTest),
                                      ('/c',Ctest),
                                      ('/t',T),
                                      ],
                                     debug=True)

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
