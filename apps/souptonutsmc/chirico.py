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
     mydb = MyDB()
     mydb.content="stuff"
     mydb.put()
     self.redirect('/cron/test')

   def get(self):
      self.response.headers['Content-Type'] = "text"
      if "98.235.187.223" == self.request.remote_addr:
        junk = Junk()
        junk.s =  str(self.request.get('stuff').rstrip())
        junk.put()
        self.response.out.write('test called in chirico: '+ str(self.request.remote_addr) )
      else:
        self.response.out.write('Your ipaddress: '+ str(self.request.remote_addr) )
      self.response.out.write("\n")
      self.response.out.write(str(self.request.query_string))
 


class TestDelete(webapp.RequestHandler):
   def get(self):
      db.delete(Junk.all().fetch(100))
      self.response.out.write('At least 100 records deleted from junk')




def main():
  application = webapp.WSGIApplication(
                                       [
                                        ('/chirico/test', Test),
                                        ('/chirico/testd', TestDelete),

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
   main()

