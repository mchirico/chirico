#
# https://souptonutsmc.appspot.com/secure/test
#
import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
# Adding users as a test
from google.appengine.api import users
from google.appengine.api import mail
import cgi
import wsgiref.handlers


from google.appengine.api import users
from google.appengine.ext import webapp

# Want to import your database definitions
from dataModels import *





class Test(webapp.RequestHandler):
   def post(self):
      allowed=["mchirico","dev.mchirico"]
      if str(users.get_current_user()) in allowed:
         s=str(users.get_current_user())
      else:
         return

   def get(self):
      allowed=["mchirico","dev.mchirico"]
      if str(users.get_current_user()) in allowed:
         s=str(users.get_current_user())
      else:
         return

      junk = Junk()
      junk.s =  s+" "+self.request.get('stuff').rstrip()
      junk.put()
      self.response.out.write('test called in chirico: '+ str(self.request.remote_addr) )
      self.response.out.write("<br>")
      self.response.out.write(str(self.request.query_string))
      self.response.out.write("current_user: ")
      self.response.out.write(str(users.get_current_user()))
 


class TestDelete(webapp.RequestHandler):
   def get(self):
      db.delete(Junk.all().fetch(100))
      self.response.out.write('At least 100 records deleted from junk')




def main():
  application = webapp.WSGIApplication(
                                       [
                                        ('/secure/test', Test),
                                        ('/secure/testd', TestDelete),

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
   main()

