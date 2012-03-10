import os
import thread
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import urlfetch
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.api import users
import cgi
import wsgiref.handlers

from dataModels import *


def addrunning(author=False,notes=False,miles=False,time=False,effort=False):
    if author and notes and miles:
     rs=Running()
     rs.author=author
     rs.notes=notes
     rs.miles=miles
     rs.put()
     return True
    return False

def getrunning(self):
    r = db.GqlQuery("SELECT * FROM Running ORDER BY timeEnter DESC LIMIT 100")
    for i in r:
      self.response.out.write('Author: '+str(i.author)+' Notes:'+str(i.notes)+' Miles:'+str(i.miles)+'\n')






class Run(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    addrunning(users.get_current_user(),self.request.get('notes').rstrip(),self.request.get('miles').rstrip())
    getrunning(self)
    s='test '
    self.response.out.write(s)
  def post(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s='you hit Run Post\n'
    self.response.out.write(s)


class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    user = users.get_current_user()
    if str(user.email()) != 'mchirico@gmail.com':
        self.response.out.write('Not registered user ->'+str(user)+'<-')
        return

    s=range(1,7)
    self.response.out.write(s)
    self.response.out.write(user.email())

application = webapp.WSGIApplication(
                                     [('/', MainPage),
                                      ('/run',Run),
                                      ],
                                     debug=True)


def checkuser(n):
    user = users.get_current_user()
    if str(user.email()) != n:
        return False
    return True

def main():
  if checkuser('mchirico@gmail.com') == True:
    run_wsgi_app(application)

if __name__ == "__main__":
  main()
