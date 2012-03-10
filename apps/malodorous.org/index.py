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
import datetime

class Dtest(db.Model):
  date = db.DateTimeProperty()
  stuff = db.StringProperty()
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

class MList(db.Model):
  f = db.ListProperty(float)
  i = db.ListProperty(long)
  s = db.StringListProperty()
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

class Story(db.Model):
  title = db.StringProperty()
  body = db.TextProperty()
  created = db.DateTimeProperty(auto_now_add=True)
    

def stp(n):
  s=""
  d=""
  for i in n:
    s=s+d+str(int(i))
    d=","
  return s


def testChart():
  k="Purple|Green|Red"
  s="""<img src=
"http://chart.apis.google.com/chart?chxt=x,y,r,x&amp;chxl=0:|2008-08-30 20:05:57|%s|1:|0|10|20|30|40|50|60|70|80|90|100|2:|A|B|C|3:|2005|2006|2007&amp;cht=lc&amp;
chd=t:10,50,30,30,90,20|1,2,100,4,5,6&amp;chls=2.0&amp;chs=800x200&amp;chf=c,ls,0,EEEEFF,0.1,FFFFFF,0.1&amp;chm=o,FF9900,0,4.0,15.0
&amp;chco=0000ff,ff00ff,000000&amp;chm=o,FF9900,0,4.0,15.0|h,000000,0,0.70,0.5|h,000000,0,0.32,0.5" /> 
"""%k
  return s




def chartBubble(a,b,c):
  s="""
<img
  src="http://chart.apis.google.com/chart?cht=s&amp;chd=t:%s|%s|%s&amp;chxt=x,y&amp;chxl=0:|0|10|20|30|40|50|60|70|80|90|100|1:|0|20|40|60|80|100&amp;chs=800x250&amp;chco=0000ff,0000ff,000000&amp;chf=c,ls,0,EEEEFF,0.1,FFFFFF,0.1&amp;chg=10,20,1,5&chm=o,FF9900,0,4.0,15.0|h,000000,0,0.70,0.5|h,000000,0,0.32,0.5" alt="Scatter plot with default blue circle data points in different sizes as defined by a third data set" /><br />
   """%(stp(a),stp(b),stp(c))
  return s



class Chart(webapp.RequestHandler):
  def get(self):
#      self.response.headers['Content-Type'] = 'text/plain'


      s="""
<img
  src="http://chart.apis.google.com/chart?cht=s&amp;chd=t:0,50,2,30,4,5,100|0,10,20,30,40,50,60|100,100,30,40,50,60,70&amp;chxt=x,y&amp;chxl=0:|0|10|20|30|40|50|60|70|80|90|100|1:|0|20|40|60|80|100&amp;chs=800x200&amp;chco=0000ff,0000ff,000000&amp;chf=c,ls,0,EEEEFF,0.1,FFFFFF,0.1&amp;chg=10,20,1,5" alt="Scatter plot with default blue circle data points in different sizes as defined by a third data set" /><br />
   """
      self.response.out.write(s)
      self.response.out.write("<br>")
      self.response.out.write(chartBubble(range(1,100),range(1,100),range(1,100)))


class Add2(webapp.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'
      self.response.out.write("add2")
      c = MList()
      c.f = [2.5,3.0,5.4,2.4]
      c.i = range(1,34)
      c.s = ['one','two','three']
      c.put()




class Add(webapp.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'
      tt = datetime.datetime.today()
      td = datetime.datetime(tt.year, tt.month, tt.day)  # day only, with 
      w=Dtest(date=td,stuff='Stuff')
      self.response.out.write(w.to_xml())
      w.put() 
      self.response.out.write("add")


class TestChart(webapp.RequestHandler):
  def get(self):
    self.response.out.write('TestChart')
    self.response.out.write(testChart())

class Test2(webapp.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'
      t="""

This is text of the document



and a bit more


"""
      s = Story(title="The Three Little Pigs",body=t)
      s.put()



class Test(webapp.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'

      tt = datetime.datetime.today()
      td = datetime.datetime(tt.year, tt.month, tt.day)  # day only, with 
# Wow. You need a space in >= 
      r=Dtest.all().filter('timeEnter >= ',td).fetch(10)
#      x=Dtest.all().filter('timeEnter >= ',td).to_xml()
      for i in r:
          self.response.out.write(str(i.date))
          self.response.out.write('\n')
      self.response.out.write('Test')
      self.response.out.write('')

class MainPage(webapp.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'
      s=datetime.datetime.now()
      self.response.out.write(str(s))



application = webapp.WSGIApplication(
                                     [('/', MainPage),
                                      ('/test',Test),
                                      ('/test2',Test2),
                                      ('/add',Add),
                                      ('/add2',Add2),
                                      ('/c',Chart),
                                      ('/d',TestChart),
                                      ],
                                     debug=True)

     

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
