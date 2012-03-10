"""
This website is accessed at the following:

https://mchiricosecure.appspot.com/

"""



import os
import thread
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import urlfetch
from google.appengine.ext.webapp.util import run_wsgi_app
import cgi
import wsgiref.handlers


from google.appengine.api import backends
from google.appengine.api import urlfetch
from google.appengine.api import taskqueue
from models import *

import logging




class Call(db.Model):
  start = db.DateTimeProperty()
  duration = db.IntegerProperty()



def delete5000(database):
	try:
           q = db.GqlQuery("SELECT __key__ FROM "+str(database))
	   db.delete(q.fetch(5000))
	except Exception, e:
		pass



class D(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write("Deleting directly")
    delete5000('Log')
    delete5000('Count')


class R(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write("Reset Everything. Directly")
    delete5000('Log')
    delete5000('Count')
    delete5000('LogAuth')
    delete5000('Settings')
    delete5000('Junk')




class M(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write("Massive Add")
    s='add'
    for i in range(0,4):
      taskqueue.add(url='/queue0', params={'s': s}, queue_name='queue0')



class T(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write("Deleting")
    s='del'
    taskqueue.add(url='/queued', params={'s': s}, queue_name='queued')

class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/html'
    s=range(1,20)
    self.response.out.write(s)
    s="""<br><a href=/t>deleting</a><br><a href=/d>delete directly</a><br><a href=/m>Massive Add</a>"""
    s=s+"<br><br><a href=/r>reset directly</a>"
    self.response.out.write(s)
    self.response.out.write('\n')
    taskqueue.add(url='/queue0', params={'s': s}, queue_name='queue0')



application = webapp.WSGIApplication(
                                     [('/', MainPage),
                                      ('/t',T),
                                      ('/d',D),
                                      ('/r',R),
                                      ('/m',M),
                                      ],
                                     debug=True)

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
