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

import os
os.environ['DJANGO_SETTINGS_MODULE'] = 'settings'
from google.appengine.dist import use_library
#use_library('django', '1.2')

import urllib


from google.appengine.api import users
from google.appengine.ext import blobstore
from google.appengine.ext import webapp
from google.appengine.ext.webapp import blobstore_handlers
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app

class MainHandler(webapp.RequestHandler):
    def get(self):
        user = users.get_current_user()
        if user:
            if user.user_id() != "113627741897119896619":
                self.redirect(users.create_login_url(self.request.uri))
            upload_url = blobstore.create_upload_url('/upload')
            self.response.out.write('<html><body>')
            self.response.out.write('<br>')
            self.response.out.write('<a href=https://workoutchirico.appspot.com/stat/test/> stat/test </a><br><br>')
            self.response.out.write('<form action="%s" method="POST" enctype="multipart/form-data">' % upload_url)
            self.response.out.write("""Upload File: <input type="file" name="file"><br> <input type="submit" name="submit" value="Submit"> </form></body></html>""")

            h={}
            for b in blobstore.BlobInfo.all():
                h[b.filename]=b.key()

            for filename in sorted(h.keys(),reverse=True):
                self.response.out.write('<li><a href="/serve/%s' % str(h[filename]) + '">' + str(filename) + '</a>')
                self.response.out.write(' <a href="/stat/%s' % str(h[filename]) + '">(Stats and Load)</a>')
                self.response.out.write(' <a href="/stat/test/%s' % str(h[filename]) + '">(Detail)</a>')
                self.response.out.write('&nbsp;&nbsp; <a href="/stat/summary/%s' % str(h[filename]) + '"> (Summary)</a>')

        else:
            self.redirect(users.create_login_url(self.request.uri))

class UploadHandler(blobstore_handlers.BlobstoreUploadHandler):
    def post(self):
        user = users.get_current_user()
        if user.user_id() == "113627741897119896619":
            upload_files = self.get_uploads('file')
            blob_info = upload_files[0]
            self.redirect('/')
        else:
            self.redirect(users.create_login_url(self.request.uri))


class ServeHandler(blobstore_handlers.BlobstoreDownloadHandler):
    def get(self, blob_key):
        blob_key = str(urllib.unquote(blob_key))
        if not blobstore.get(blob_key):
            self.error(404)
        else:
            self.send_blob(blobstore.BlobInfo.get(blob_key), save_as=True)

class Test(webapp.RequestHandler):
    def get(self):
        for b in blobstore.BlobInfo.all():
            blob_reader = blobstore.BlobReader(b.key())
            data = blob_reader.read()
            self.response.out.write(str(data)+str(b.size))
            for i in range(0,20):
                self.response.out.write('<br>')


def main():
    application = webapp.WSGIApplication(
          [('/', MainHandler),
           ('/upload', UploadHandler),
           ('/serve/([^/]+)?', ServeHandler),
           ('/test', Test),
          ], debug=True)
    run_wsgi_app(application)

if __name__ == '__main__':
  main()


