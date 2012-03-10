#
# Copyright 2011 CWXSTAT Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
__author__ = 'mchirico@gmail.com (Mike Chirico)'

import os
import logging
import urllib
import xml.etree.ElementTree 
import datetime
from math import sqrt,sin,cos,asin,pi,ceil,fabs


from google.appengine.api import users
from google.appengine.ext import blobstore
from google.appengine.ext import webapp
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.ext import db

from google.appengine.api import taskqueue
from google.appengine.api import backends
from google.appengine.api import urlfetch


import models


dateformat='%Y-%m-%dT%H:%M:%SZ'
strptime=datetime.datetime.strptime




class QueueD(webapp.RequestHandler):
    def post(self):
        s = str(self.request.get('s'))
	try:
                payload='data'
		url = '%s/mega/del' % backends.get_url('mega')
		urlfetch.fetch(url, method='POST', payload=payload)
	except Exception, e:
		pass


class Queue0(webapp.RequestHandler):
    def post(self):
        s = str(self.request.get('s'))
	try:
                payload='data'
		url = '%s/mega/inc' % backends.get_url('mega')
		urlfetch.fetch(url, method='POST', payload=payload)
	except Exception, e:
		pass


class Queue2(webapp.RequestHandler):
    def post(self):
        s = str(self.request.get('s'))
	try:
                payload='data'
		url = '%s/mega/tst' % backends.get_url('mega')
		urlfetch.fetch(url, method='POST', payload=payload)
	except Exception, e:
		pass



def main():
    application = webapp.WSGIApplication(
          [
	   ('/queued', QueueD),
	   ('/queue0', Queue0),
	   ('/queue2', Queue2),
          ], debug=True)
    run_wsgi_app(application)

if __name__ == '__main__':
  main()


