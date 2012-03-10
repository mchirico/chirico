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

import random
from google.appengine.api import backends
from google.appengine.api import urlfetch

counters = ['counter-%d' % i for i in xrange(10)]

url = '%s/backend/counter/inc' % backends.get_url('counter')
while True:
  payload = 'name=%s&delta=1' % random.choice(counters)
  urlfetch.fetch(url, method='POST', payload=payload)
