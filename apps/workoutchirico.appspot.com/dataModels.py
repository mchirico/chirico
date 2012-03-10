from google.appengine.ext import db
def spam(text):
    return text + ' spam\n'

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
  date = db.DateTimeProperty()
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

class Running(db.Model):
  author = db.UserProperty()
  notes = db.StringProperty(multiline=True)
  miles = db.StringProperty()
  time = db.StringProperty()
  effort = db.StringProperty()
  timeEnter = db.DateTimeProperty(auto_now_add=True)    

