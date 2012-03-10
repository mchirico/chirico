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



def getSettings(n=0):
    q = Settings.all()
    q.filter('count = ',n)
    results = q.fetch(1)
    if len(results) == 0:
        q=Settings()
        q.count=n
        q.md5sum=configs.md5sum
        q.put()
        return configs.md5sum
    else:
        return str(results[0].md5sum)




class T(webapp.RequestHandler):
    def get(self,method):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.out.write('You need to post key')
        self.response.out.write('\n')


    def post(self, method):
        self.response.headers['Content-Type'] = 'text/plain'
        mkey=str(self.request.get('md5sum'))
        if mkey == getSettings(0):
            self.response.out.write(getSettings(0))
            q=LogAuth()
            q.log='was go mkey('+mkey+') getSettings: ('+getSettings(0)+')'
            q.ip=self.request.remote_addr
            q.put()
        else:
            self.response.out.write('FAIL')
            q=LogAuth()
            q.log='MISMATCH: mkey('+mkey+') getSettings: ('+getSettings(0)+')'
            q.ip=self.request.remote_addr
            q.put()




application = webapp.WSGIApplication(
                                     [(r'/showsettings/(get|inc|dec|del|tst)$', T)],
                                     debug=True)



def main():
    run_wsgi_app(application)


if __name__ == "__main__":
    main()




