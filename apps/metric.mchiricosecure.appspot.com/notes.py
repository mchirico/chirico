import os
import urllib

from google.appengine.api import users
from google.appengine.ext import blobstore
from google.appengine.ext import webapp
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app


class Notes(webapp.RequestHandler):
    def get(self):
        f=open('Notes')
        m=f.readlines()
        f.close()
        for i in m:
            self.response.out.write(i.strip())
            self.response.out.write("<br>")



def main():
    application = webapp.WSGIApplication(
          [('/notes', Notes),
          ], debug=True)
    run_wsgi_app(application)

if __name__ == '__main__':
  main()


