"""
This website is accessed at the following:

https://physiostatweb.appspot.com/



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
from dataModels import *

class Call(db.Model):
  start = db.DateTimeProperty()
  duration = db.IntegerProperty()


class Test(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s='you hit test. Should create database.\n'
    workOutdb = WorkoutLog()
    workOutdb.status='yes';
    workOutdb.put()
    self.response.out.write(s)

class TestHtml(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s='you hit test.html\n'
    self.response.out.write(s)


class D(webapp.RequestHandler):
  def get(self):
    a=[1,2,4]
    template_values = {
      'array': a,
      }
    path = os.path.join(os.path.dirname(__file__), 'dindex.html')
    self.response.out.write(template.render(path, template_values))

class T(webapp.RequestHandler):
  def get(self):

    exec("a=[1,2,3,4,5,6,7,8,9]")
    url='t'
    url_linktext='mikechirico'
    result = urlfetch.fetch('http://mikechirico.com/test')
    template_values = {
      'array': a,
      'result': result.content,
      'url': url,
      'url_linktext': url_linktext,
      }

    path = os.path.join(os.path.dirname(__file__), 'index.html')
    self.response.out.write(template.render(path, template_values))


class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s=range(1,20)
    self.response.out.write(s)

application = webapp.WSGIApplication(
                                     [('/', MainPage),
                                      ('/test',Test),
                                      ('/test.html',TestHtml),
                                      ('/t',T),
                                      ('/d',D),
                                      ],
                                     debug=True)

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
