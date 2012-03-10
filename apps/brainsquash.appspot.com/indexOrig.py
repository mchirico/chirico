import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import mail
import cgi
import wsgiref.handlers

from google.appengine.api import users
from google.appengine.ext import webapp

# Want to import your database definitions
from dataModels import *



# This is for profiling
def profile_main():
 import cProfile, pstats
 prof = cProfile.Profile()
 prof = prof.runctx("main()", globals(), locals())
 print "<pre>"
 stats = pstats.Stats(prof)
 stats.sort_stats("time")  # Or cumulative
 stats.print_stats(80)  # 80 = how many to print
 # The rest is optional.
 # stats.print_callees()
 # stats.print_callers()
 print "</pre>"





class MainPage(webapp.RequestHandler):
  def get(self):
    computers_query = Computer.all().order('hostname')
    computers = computers_query.fetch(20)


    if users.get_current_user():
      url = users.create_logout_url(self.request.uri)
      url_linktext = 'Logout'
    else:
      url = users.create_login_url(self.request.uri)
      url_linktext = 'Login'

    template_values = {
      'computers': computers,
      'url': url,
      'url_linktext': url_linktext,
      }

    path = os.path.join(os.path.dirname(__file__), 'index.html')
    self.response.out.write(template.render(path, template_values))

    





class Guestbook(webapp.RequestHandler):
  def post(self):
    computer = Computer()

    if users.get_current_user():
      computer.author = users.get_current_user()

#    computer.content = self.request.get('content')
#    computer.put()
    self.redirect('/')


class Action0(webapp.RequestHandler):
  def post(self):
    computer = Computer()

    if users.get_current_user():
      computer.author = users.get_current_user()

    computer.content = "Action 0"
    computer.put()

    message = mail.EmailMessage(sender="mchirico@gmail.com",
              subject="Your account has been approved")
    message.to = "Mike Chirico <mchirico@cwxstat.org>"
    message.body = """
    This is a sample body
"""
    message.send()

    self.redirect('http://www.chirico.org')



class Test(webapp.RequestHandler):
   def post(self):
     mydb = MyDB()
     mydb.content="stuff"
     mydb.put()
     self.redirect('/')

   def get(self):
     self.response.out.write('test version 1.0')




class Notes(webapp.RequestHandler):
  def get(self):

    version = '0.0.1'
    email = 'mchirico@gmail.com'
    homepage = 'http://souptonuts.sourceforge.net/chirico/'
    template_values = {
      'version': version,
      'email': email,
      'homepage': homepage,
      }
    path = os.path.join(os.path.dirname(__file__), 'notes.html')
    self.response.out.write(template.render(path, template_values))



class MDELETE(webapp.RequestHandler):
  def post(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cron.all().fetch(100))

  def get(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cron.all().fetch(100))



def mainDELETE():
  application = webapp.WSGIApplication(
                                       [('/', MDELETE),
                                        ('/sign', MDELETE),
                                        ('/Action0', MDELETE),
                                        ('/test', MDELETE),
                                        ('/notes', MDELETE),
                                        ('/notes.html', MDELETE)
                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

def main():
  application = webapp.WSGIApplication(
                                       [('/', MainPage),
                                        ('/sign', Guestbook),
                                        ('/Action0', Action0),
                                        ('/test', Test),
                                        ('/notes', Notes),
                                        ('/notes.html', Notes)
                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
#  profile_main()
# Normally you just want main
#    mainDELETE()
   main()

