#!/usr/bin/env python
#
# Copyright 2011 Google Inc. All Rights Reserved.
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
# vim: set ts=4 sw=4 et tw=79:
"""Simple frontend that communicates with a counting backend."""

__author__ = 'Greg Darke <darke@google.com>'

import os
import urllib

from google.appengine.api import backends
from google.appengine.api import urlfetch
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template
from google.appengine.ext.webapp.util import run_wsgi_app


TEMPLATE_ROOT = os.path.dirname(__file__)


def _call_counter_method(method, name, delta='0'):
    """Call 'method' on the counter backend.

    Args:
      method: The method. One of 'inc', 'dec', 'get'.
      name: The counter to apply 'method' to.
      delta: The amount to increase/decrease the counter.

    Returns: An instance of urlfetch._URLFetchResult
    """
    payload = urllib.urlencode({'name': name, 'delta': delta})
    url = '%s/backend/counter/%s' % (backends.get_url('counter'), method)
    return urlfetch.fetch(url, method='POST', payload=payload)


class MainHandler(webapp.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        self.response.out.write('Test:'+ TEMPLATE_ROOT )




_handlers = [(r'/', MainHandler)]
application = webapp.WSGIApplication(_handlers)


def main():
    run_wsgi_app(application)

if __name__ == '__main__':
    main()
