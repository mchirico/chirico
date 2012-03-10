from google.appengine.ext import db
def pr(text):
    return text + ' pr test\n'

class C1():
    def __init__(self,who='joe'):
        self.name = who

    def setname(self, who):
        self.name = who

class WorkoutLog(db.Model):
  author = db.UserProperty()
  workoutDesc = db.StringProperty(multiline=True)
  heartRate = db.StringProperty()
  hostname = db.StringProperty()
  status = db.StringProperty()
  date = db.DateTimeProperty(auto_now_add=True)    



