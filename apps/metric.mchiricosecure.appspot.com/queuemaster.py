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
R=6371.0008 # Earth volumetric radius
milesperkm=0.621371192
feetperm=3.2808399
strptime=datetime.datetime.strptime



def haversin(theta):
	return sin(0.5*theta)**2

def distance(p1,p2):
        lat1,lon1=[a*pi/180.0 for a in p1]
        lat2,lon2=[a*pi/180.0 for a in p2]
        deltalat=lat2-lat1
        deltalon=lon2-lon1
        h=haversin(deltalat)+cos(lat1)*cos(lat2)*haversin(deltalon)
        dist=2*R*asin(sqrt(h))
        return dist


def delete200(database):
	try:
           q = db.GqlQuery("SELECT __key__ FROM "+str(database))
	   db.delete(q.fetch(200))
	except Exception, e:
		pass


"""

class Author(db.Model):
    name = db.StringProperty()

class Story(db.Model):
    author = db.ReferenceProperty(Author)

story = db.get(story_key)
author_name = story.author.name

"""


class StatHandler(blobstore_handlers.BlobstoreDownloadHandler):
    def get(self, blob_key):
        blob_key = str(urllib.unquote(blob_key))
        if not blobstore.get(blob_key):
            self.error(404)
        else:
            taskqueue.add(url='/queue0', params={'blob_key': blob_key, 'author': users.get_current_user()}, queue_name='queue0')
            blob_reader = blobstore.BlobReader(blob_key)
            data = blob_reader.read()
            t=xml.etree.ElementTree.fromstring(data)
	    pre_lat,pre_long,pre_time,pre_alt,pre_heart=None,None,None,None,None
	    t_dist=0
	    t_alt=0
            for e in t.getiterator():
		if e.tag.find("Time") >0:
			time=e.text
		if e.tag.find("LatitudeDegrees") >0:
			lat=float(e.text)
		if e.tag.find("LongitudeDegrees") >0:
			long=float(e.text)
		if e.tag.find("AltitudeMeters") >0:
			alt=float(e.text)
		if e.tag.find("HeartRateBpm") >0:
			heart= int(e[0].text)
			if pre_lat != None:
				delta=distance([lat,long],[pre_lat,pre_long])
				if fabs(alt-pre_alt) >= 1.2:
					t_alt=t_alt+fabs(alt - pre_alt)
				t_dist+=delta
				self.response.out.write(time +', '+str(lat)+', '+str(long)+ ', '+str(alt)+', '+str(heart)+', '+str(delta)+', '+str(t_dist)+', Miles: '+str(t_dist*milesperkm)+',  Total Alt: '+str(t_alt)+"<br>")
			pre_lat,pre_long,pre_time,pre_alt,pre_hr=lat,long,time,alt,heart









class Queue0(webapp.RequestHandler):
    def post(self):
        author = str(self.request.get('author'))
	blob_key = str(self.request.get('blob_key'))
	q = EntryIndex.all()
        q.filter("author =", users.User(author))
	q.filter("blob_key =", blob_key)
	if q.count() > 0:
		return

	def txn():
		entryindex = EntryIndex()
		entryindex.author= users.User(author)
		entryindex.blob_key= blob_key
		entryindex.put()
	db.run_in_transaction(txn)
		

        if not blobstore.get(blob_key):
            return
        else:
            blob_reader = blobstore.BlobReader(blob_key)
            data = blob_reader.read()
            t=xml.etree.ElementTree.fromstring(data)
	    pre_lat,pre_long,pre_time,pre_alt,pre_heart=None,None,None,None,None
	    t_dist=0
	    t_alt=0
	    rec=0
            for e in t.getiterator():
		if e.tag.find("Time") >0:
			time=e.text
		if e.tag.find("LatitudeDegrees") >0:
			lat=float(e.text)
		if e.tag.find("LongitudeDegrees") >0:
			long=float(e.text)
		if e.tag.find("AltitudeMeters") >0:
			alt=float(e.text)
		if e.tag.find("HeartRateBpm") >0:
			heart= int(e[0].text)
			if pre_lat != None:
				delta=distance([lat,long],[pre_lat,pre_long])
				if fabs(alt-pre_alt) >= 1.2:
					t_alt=t_alt+fabs(alt - pre_alt)
				t_dist+=delta
				taskqueue.add(url='/queue1', params={'author': author,
                                                                             'blob_key': blob_key,
									     'lat': lat,
									     'long':long,
									     'rec':rec,
									     'heart':heart,
									     'alt':alt,
									     't_alt':t_alt,
									     'dist':delta,
									     't_dist':t_dist,
									     'time':time}, queue_name='queue1')
			pre_lat,pre_long,pre_time,pre_alt,pre_hr=lat,long,time,alt,heart
			rec = rec +1






class Queue1(webapp.RequestHandler):
    def post(self):
        author = self.request.get('author')
	blob_key = self.request.get('blob_key')
	lat = self.request.get('lat')
	long = self.request.get('long')
	time = self.request.get('time')
	rec = int(self.request.get('rec'))
	alt = float(self.request.get('alt'))
	t_alt = float(self.request.get('t_alt'))
	dist = float(self.request.get('dist'))
	t_dist = float(self.request.get('t_dist'))
	heart = int(self.request.get('heart'))
        def txn():
	    parsedpts = ParsedPts()
	    parsedpts.author= users.User(author)
	    parsedpts.blob_key= blob_key
	    parsedpts.rec = rec
	    parsedpts.alt = alt
	    parsedpts.t_alt = t_alt
	    parsedpts.dist = dist
	    parsedpts.t_dist = t_dist
	    parsedpts.heart = heart
	    parsedpts.date = strptime(time,dateformat)
	    parsedpts.pt = db.GeoPt(lat,long)
	    parsedpts.put()
        db.run_in_transaction(txn)


class Queue2(webapp.RequestHandler):
    def post(self):
        database = self.request.get('database')
	q = db.GqlQuery("SELECT __key__ FROM "+str(database))
	count = q.count(None)
	for i in range(0,count/200+1):
		taskqueue.add(url='/queue3', params={'database': database}, queue_name='queue3')


class Queue3(webapp.RequestHandler):
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





class Delete(webapp.RequestHandler):
    def get(self,data):
        database='ParsedPts'
        q = db.GqlQuery("SELECT __key__ FROM "+str(database))
        self.response.out.write('test:  Count='+str(q.count(None))+'<br>')
	taskqueue.add(url='/queue2', params={'database': database}, queue_name='queue2')

        q = db.GqlQuery("SELECT __key__ FROM "+str(database))
        self.response.out.write('test:  Count='+str(q.count(None))+'<br>')
	q = EntryIndex.all()
        q.filter("author =", users.User('mchirico'))
        self.response.out.write('Count on EntryIndex '+ str(q.count()))



class Dev(webapp.RequestHandler):
    def get(self,blob_key):
        self.response.out.write('This is a test')
	count = models.Count()
	count.count = 1
	count.put()


class Test(webapp.RequestHandler):
    def get(self,blob_key):
        blob_key = str(urllib.unquote(blob_key))
	q = ParsedPts.all()
	q.filter("author =", users.User('mchirico'))
	q.filter("blob_key =", blob_key)
	q.order("rec")

	m150=0
	a=0
	b=0
	results = q.fetch(5000)
	for p in results:
		if int(p.heart) >= 150:
			self.response.out.write('rec,'+str(p.rec)+','+str(p.heart)+','+str(p.date)+'<br>')
		if int(p.heart) >= 150 and a==0:
			a=strptime(str(p.date), "%Y-%m-%d %H:%M:%S")
		if int(p.heart) < 150 and a != 0:
			b=strptime(str(p.date), "%Y-%m-%d %H:%M:%S")
			m150 = m150 + (b-a).seconds
			a=0
			b=0

        database='ParsedPts'
        q = db.GqlQuery("SELECT __key__ FROM "+str(database))
        self.response.out.write('test:  Count='+str(q.count(None))+'<br>')
	q = EntryIndex.all()
        q.filter("author =", users.User('mchirico'))
        self.response.out.write('Count on EntryIndex '+ str(q.count()))
	for i in range(0,5):
		self.response.out.write('<br>')
	self.response.out.write('Seconds Above 150: '+str(m150))
		




class Summary(webapp.RequestHandler):
    def get(self,blob_key):
        blob_key = str(urllib.unquote(blob_key))
	q = ParsedPts.all()
	q.filter("author =", users.User('mchirico'))
	q.filter("blob_key =", blob_key)
	q.order("rec")
	results = q.fetch(5000)
	b = libst.Bhtable()
	tot = b.cal(results) 

	logging.debug('tot='+str(len(tot)))

	for i in tot:
		if tot[i] > 0:
			self.response.out.write('HR  '+str(i)+' Time ('+str(tot[i]/60)+':'+str(tot[i]-tot[i]/60*60)+')<br>')








def main():
    application = webapp.WSGIApplication(
          [
           ('/stat/dev/([^/]+)?', Dev),
           ('/stat/test/([^/]+)?', Test),
           ('/stat/delete/([^/]+)?', Delete),
           ('/stat/summary/([^/]+)?', Summary),
           ('/stat/([^/]+)?', StatHandler),
	   ('/queue0', Queue0),
	   ('/queue1', Queue1),
	   ('/queue2', Queue2),
	   ('/queue3', Queue3),
          ], debug=True)
    run_wsgi_app(application)

if __name__ == '__main__':
  main()


