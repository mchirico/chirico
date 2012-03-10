from google.appengine.ext import db
from google.appengine.ext import search

##################################################################################
#                                                                                #
#                       Models                                                   #
#                                                                                #
##################################################################################



class Log(db.Model):
  count = db.IntegerProperty()
  log = db.StringProperty(multiline=True)
  txt = db.TextProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)


class LogAuth(db.Model):
  count = db.IntegerProperty()
  log = db.StringProperty(multiline=True)
  ip = db.StringProperty()
  txt = db.TextProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)



class Settings(db.Model):
  count = db.IntegerProperty()
  md5sum = db.StringProperty()
  ip = db.StringProperty()
  txt = db.TextProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

class Junk(db.Model):
  count = db.IntegerProperty()
  log = db.StringProperty()
  list = db.StringListProperty()
  txt = db.TextProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

class Count(db.Model):
  count = db.IntegerProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

class Count2(db.Model):
  count = db.IntegerProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

