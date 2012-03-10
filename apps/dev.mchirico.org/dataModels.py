from google.appengine.ext import db
def pr(text):
    return text + ' pr test\n'

class C1():
    def __init__(self,who='joe'):
        self.name = who

    def setname(self, who):
        self.name = who

class Cron(db.Model):
  author = db.UserProperty()
  content = db.StringProperty(multiline=True)
  hash = db.StringProperty()
  action = db.StringProperty()
  actionTag = db.StringProperty()
  actionRows = db.StringProperty()
  hostname = db.StringProperty()
  status = db.StringProperty()
  date = db.DateTimeProperty(auto_now_add=True)    

class Computer(db.Model):
  author = db.UserProperty()
  computerkey = db.StringProperty()
  hostname = db.StringProperty(multiline=True)
  date = db.DateTimeProperty(auto_now_add=True)

class Cstat(db.Model):
  author = db.UserProperty()
  computerkey = db.StringProperty()
  hostname = db.StringProperty(multiline=True)
  ip = db.StringProperty()
  uptime = db.StringProperty(multiline=True)
  iostat = db.TextProperty()
  mtop = db.TextProperty()
  slabinfo = db.TextProperty()
  version = db.StringProperty()
  date = db.DateTimeProperty(auto_now_add=True)

class Junk(db.Model):
  s = db.StringProperty(multiline=True)

