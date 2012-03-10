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

# Local Libs
import libst
from databases import *
import models


dateformat='%Y-%m-%dT%H:%M:%SZ'
dateformat='%m/%d/%y %H:%M:%S'
strptime=datetime.datetime.strptime




class Dev(webapp.RequestHandler):
    def get(self,blob_key = '0'):
        user=users.get_current_user()
        if str(user) != 'mchirico':
            return
        blobid='AMIfv9688orFM57N5a7gxlm1GhkQwRK1_Lxl2bT9b2sbQNUv_WneCeSCxs7fzceQgep6qXdVK8ac7WjtXddOpL_y0_Uo1IhTbSYmWtTNr795l0aCZYKHeqWtQq_eSP0bnW1yVcN8J8Pd5tXf0oTDxvAFz_EdTwx_2g'
        self.response.out.write('Dev: '+str(users.get_current_user())+ str('<br>'))
        runRecords(blobid,self)





def runRecords(blobid,self):
    blob_info = blobstore.BlobInfo.get(blobid)
    total_size=blob_info.size
    recs=500000
    offset=0
    number_of_runs = int(ceil(total_size/float(recs)))
    a = Accumulator()
    a.counter = number_of_runs
    a.put()
#    deleteDatabase('Queue')
    self.response.out.write('Number of runs:'+str(number_of_runs))
"""
    while offset <= blob_info.size:
        blob_reader = blobstore.BlobReader(blobid,recs,offset)
        data = blob_reader.readlines(recs)
        blob_reader.close()
        m=[i.split() for i in data]
#    deleteDatabase('Queue')
        for i in m:
            pushAddToQueue(i,self)
        offset+=recs
        
"""


def increment_counter(key, amount):
    obj = db.get(key)
    obj.counter += amount
    obj.put()







class queueRunRecords(webapp.RequestHandler):
    def post(self):
        date_  = self.request.get('date')
        time_  = self.request.get('time')
        mdate = strptime(str(date_+' '+time_),dateformat)
        queue = self.request.get('queue')
        name =  self.request.get('name')
        ready = int(self.request.get('ready'))
        wait  = int(self.request.get('wait'))
        avg =   float(self.request.get('avg'))
#        logging.debug('In queue:'+str(avg))
        def txn():
            q = Queue()
            q.mdate =  mdate
            q.queue =  queue
            q.name  =  name
            q.ready =  ready
            q.wait  =  wait
            q.avg   =  avg
            q.put()
        db.run_in_transaction(txn)





def pushAddToQueue(N,self):
        if len(N) == 9:
            if N[2] in ['TFJMSA','TFJMSE','TFJMSI']:
                self.response.out.write('HERE:'+str(N[2])+':<br>')
                taskqueue.add(url = '/queueAddToQueue', params={'date': N[0],
                                                           'time': N[1],
                                                           'queue': N[2],
                                                           'name': N[3],
                                                           'ready': N[5],
                                                           'wait': N[7],
                                                           'avg': N[8]}, queue_name='queueAddToQueue')






class queueAddToQueue(webapp.RequestHandler):
    def post(self):
        date_  = self.request.get('date')
        time_  = self.request.get('time')
        mdate = strptime(str(date_+' '+time_),dateformat)
        queue = self.request.get('queue')
        name =  self.request.get('name')
        ready = int(self.request.get('ready'))
        wait  = int(self.request.get('wait'))
        avg =   float(self.request.get('avg'))
#        logging.debug('In queue:'+str(avg))
        def txn():
            q = Queue()
            q.mdate =  mdate
            q.queue =  queue
            q.name  =  name
            q.ready =  ready
            q.wait  =  wait
            q.avg   =  avg
            q.put()
        db.run_in_transaction(txn)



def deleteDatabase(database):
    for i in range(0,2000):
        taskqueue.add(url = '/queueDeleteDatabase', params={'database': str(database)}, queue_name='queueDeleteDatabase')



class queueDeleteDatabase(webapp.RequestHandler):
    def post(self):
        database = self.request.get('database')
        def delete200(database):
           try:
                q = db.GqlQuery("SELECT __key__ FROM "+str(database))
		if q.count() > 0:
			db.delete(q.fetch(200))
	   except Exception, e:
		pass
        delete200(database)


def main():
    application = webapp.WSGIApplication(
          [
           ('/dev/([^/]+)?', Dev),
           ('/queueAddToQueue',queueAddToQueue),
           ('/queueDeleteDatabase',queueDeleteDatabase),
           ('/queueRunRecords',queueRunRecords),
          ], debug=True)
    run_wsgi_app(application)


if __name__ == '__main__':
  main()
