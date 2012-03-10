#!/usr/bin/env python
#
#
# Copyright 2011 CWXSTAT Inc. www.cwxstat.com
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



__author__ = 'Mike Chirico <mchirico@gmail.com>'

import math
import time

import random
from google.appengine.api import runtime
from google.appengine.api import taskqueue

from google.appengine.api import backends
from google.appengine.api import urlfetch

from google.appengine.api import users
from google.appengine.ext import blobstore
from google.appengine.ext import webapp
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app
from google.appengine.ext import db


import configs
from models import *


tmp_count=0
fetch_count=0

def myFetch(instance):

	try:
          global fetch_count
#	  fetch_count+=1
          payload = 'md5sumMyFetch=%s&instance=%s&count=%s' % (configs.md5sum,instance,fetch_count)
	  url='https://physiostatweb.appspot.com/physiostat0'
	  m=urlfetch.fetch(url, method='POST', payload=payload)
	except Exception, e:
          return str(0)
	return str(m.content)
	


def delete5000(database):
	try:
           q = db.GqlQuery("SELECT __key__ FROM "+str(database))
	   db.delete(q.fetch(5000))
	except Exception, e:
		pass

def deleteJunk(n):
	try:
           q = Junk.all()
	   q.filter("count =",n)
	   db.delete(q.fetch(5000))
	except Exception, e:
		pass


class T(webapp.RequestHandler):
    def get(self,method):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.out.write('Hello, webapp World!')
        self.response.out.write('\n')
	log('in get. method:'+str(method))

    def post(self, method):
        self.response.headers['Content-Type'] = 'text/plain'
	log('method='+str(method))
        if method == 'del':
            delete5000('Log')
            delete5000('Count')
	    log('delete 5000')
        self.response.out.write("Number in count: ")
        self.response.out.write(str(q.count()))
        self.response.out.write('\n')
        self.response.out.write('\n')
        q=Count()
        q.count=2
        q.put()





def addJunk(N=[1,2,3]):
    deleteJunk(backends.get_instance())
    q=Junk()
    q.count=backends.get_instance()
    q.txt=str('Count:'+str(tmp_count)+' Instance:'+str(backends.get_instance()) )
    q.put()


def log(s):
    global tmp_count
    tmp_count=tmp_count+1
    memory_usage = runtime.memory_usage().current()
    q=Log()
    q.count=tmp_count
    q.txt=str(memory_usage)
    q.log=s
    q.put()
    

def stuff():
    log('Stuff: version2')


application = webapp.WSGIApplication(
                                     [(r'/mega/(get|inc|dec|del|tst)$', T)],
                                     debug=True)



def main():
    log('v3')
    run_wsgi_app(application)
    stuff()
    addJunk()
    log('myFetch: '+str(myFetch(backends.get_instance())))

if __name__ == "__main__":
    main()




