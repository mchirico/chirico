import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import mail
import cgi
import wsgiref.handlers

from google.appengine.api import users
from google.appengine.ext import webapp

class Cron(db.Model):
  author = db.UserProperty()
  content = db.StringProperty(multiline=True)
  hash = db.StringProperty()
  action = db.StringProperty()
  status = db.StringProperty()
  date = db.DateTimeProperty(auto_now_add=True)



class MainPage(webapp.RequestHandler):
  def get(self):
    crons_query = Cron.all().order('-date')
    crons = crons_query.fetch(10)


    if users.get_current_user():
      url = users.create_logout_url(self.request.uri)
      url_linktext = 'Logout'
    else:
      url = users.create_login_url(self.request.uri)
      url_linktext = 'Login'

    template_values = {
      'crons': crons,
      'url': url,
      'url_linktext': url_linktext,
      }
    path = os.path.join(os.path.dirname(__file__), 'cronindex.html')
    self.response.out.write(template.render(path, template_values))




class ActionsToDo():
    def __init__(self,action='list'):
        self.action = action
        
        

    def runaction(self, action):
        self.action = action

    def list(self, tag):
      q = Cron.all()
      q.filter('action =', tag )
      s = ''
      for i in q:
        s = s + i.action + '\n'
      return s

    def delete(self, tag = ''):
     q = Cron().all()
     q.filter('action =', tag)
     for i in q:
       i.delete()

      







class FireAction(webapp.RequestHandler):
  def post(self):


# Do nothing unless we have the correct hash
    if '3ad540e4c39f54d0d138c60d66c1d923' == self.request.get('hash').rstrip():
      cron = Cron()
      cron.content = self.request.get('content')
      cron.hash = self.request.get('hash').rstrip()
      cron.action = self.request.get('action').rstrip()
      cron.status = self.request.get('status').rstrip()
      cron.put()
      self.response.out.write('Fired: ' + cron.hash +'\n')
      if cron.action == 'ActionToDo':
        self.response.out.write('Getting Ready to call \n')
        a = ActionsToDo()
        self.response.out.write(a.list('ActionToDo'))
        a.delete('ActionToDo')

    else:
      self.response.out.write('Not Fired: ' + self.request.get('hash').rstrip() +'\n')
#    self.redirect('/cron/')




class Test(webapp.RequestHandler):
   def post(self):
     mydb = MyDB()
     mydb.content="stuff"
     mydb.put()
     self.redirect('/cron/test')





def main():
  application = webapp.WSGIApplication(
                                       [('/cron/', MainPage),
                                        ('/cron/fireAction', FireAction),
                                        ('/cron/test', Test)

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()
