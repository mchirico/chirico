import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import mail
import cgi
import time
import datetime
import wsgiref.handlers

from google.appengine.api import users
from google.appengine.ext import webapp

# Want to import your database definitions
#from dataModels import *



class MainPage(webapp.RequestHandler):
  def get(self):

    version = '0.0.1'
    email = 'mchirico@gmail.com'
    homepage = 'http://souptonuts.sourceforge.net/chirico/'
    now = datetime.datetime.now()
    template_values = {
      'version': version,
      'email': email,
      'homepage': homepage,
      'now':now,
      }
    path = os.path.join(os.path.dirname(__file__), 'index.html')
    self.response.out.write(template.render(path, template_values))


class Notes(webapp.RequestHandler):
  def get(self):

    version = '0.0.1'
    email = 'mchirico@gmail.com'
    homepage = 'http://souptonuts.sourceforge.net/chirico/'
    remote_addr = os.getenv('REMOTE_ADDR');
    template_values = {
      'version': version,
      'email': email,
      'homepage': homepage,
      'remote_addr': remote_addr,
      }
    path = os.path.join(os.path.dirname(__file__), 'notes.html')
    self.response.out.write(template.render(path, template_values))




def main():
  application = webapp.WSGIApplication(
                                       [('/', MainPage),
                                        ('/notes', Notes),
                                        ('/notes.html', Notes),
                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()
