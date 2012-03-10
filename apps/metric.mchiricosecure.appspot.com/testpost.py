import os
import urllib

from google.appengine.api import users
from google.appengine.ext import blobstore
from google.appengine.ext import webapp
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app


class Test(webapp.RequestHandler):
    def get(self):
        self.response.out.write("Test on get")
        

    def post(self):
        m=self.request.get('someText')
        self.response.out.write("Test on post: "+str(m))
        


def main():
    application = webapp.WSGIApplication(
          [('/testpost', Test),
#           ('/testpost/([^/]+)?', Test),
          ], debug=True)
    run_wsgi_app(application)

if __name__ == '__main__':
  main()


