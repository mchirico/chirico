import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import mail
import cgi
import wsgiref.handlers

from google.appengine.api import users
from google.appengine.ext import webapp

from dataModels import *




class MainPage(webapp.RequestHandler):
  def get(self):
    cstats_query = Computer.all().order('-date')
    cstats = cstats_query.fetch(10)


    if users.get_current_user():
      url = users.create_logout_url(self.request.uri)
      url_linktext = 'Logout'
    else:
      url = users.create_login_url(self.request.uri)
      url_linktext = 'Login'

    template_values = {
      'cstats': cstats,
      'url': url,
      'url_linktext': url_linktext,
      }

    path = os.path.join(os.path.dirname(__file__), 'indexcstat.html')
    self.response.out.write(template.render(path, template_values))


class MDELETE(webapp.RequestHandler):
  def post(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cstat.all().fetch(100))
      db.delete(Computer.all().fetch(100))




  def get(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cstat.all().fetch(100))
      db.delete(Computer.all().fetch(100))






class Logger(webapp.RequestHandler):
  def post(self):


    if users.get_current_user():
      cstat.author = users.get_current_user()

    if self.request.get('computerkey') == 'fa794a79eb469f2b5f85c67dbad319d5':  


      m = self.request.get('hostname').strip()
      q = Computer.all()
      q.filter('hostname =', m )

      for i in q:
        self.response.out.write('Results of query: ' + i.hostname + '\n')
        i.delete()


      cstatComputers = Computer()
      cstatComputers.hostname = self.request.get('hostname').rstrip()
      cstatComputers.put()


      cstat = Cstat()
      cstat.computerkey = self.request.get('computerkey').rstrip()
      cstat.hostname = self.request.get('hostname').rstrip()
      cstat.ip = self.request.get('ip')
      cstat.uptime = self.request.get('uptime').rstrip()
      cstat.iostat = self.request.get('iostat')
      cstat.slabinfo = self.request.get('slabinfo')
      cstat.version = "2.0"
      cstat.mtop = self.request.get('top')
      cstat.put()
      self.response.out.write('DATA IN: <'+ cstat.hostname + '>\n' )
    else:
      self.response.out.write('DATA NO')


class Action0(webapp.RequestHandler):
  def post(self):
    cstat = Cstat()

    if users.get_current_user():
      cstat.author = users.get_current_user()

    cstat.content = "Action 0"
    cstat.put()

    message = mail.EmailMessage(sender="mchirico@gmail.com",
              subject="Your account has been approved")
    message.to = "Mike Chirico <mchirico@cwxstat.org>"
    message.body = """
    This is a sample body
"""
    message.send()

    self.redirect('/')



class Test(webapp.RequestHandler):
   def post(self):

     self.redirect('/')



def mainDELETE():
  application = webapp.WSGIApplication(
                                       [('/cstat/', MDELETE),
                                        ('/cstat/Logger', MDELETE),
                                        ('/cstat/Action0/', MDELETE),
                                        ('/cstat/test/', MDELETE)

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

def main():
  application = webapp.WSGIApplication(
                                       [('/cstat/', MainPage),
                                        ('/cstat/Logger', Logger),
                                        ('/cstat/Action0/', Action0),
                                        ('/cstat/test/', Test)

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()
