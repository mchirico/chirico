import os
from google.appengine.ext.webapp import template
from google.appengine.ext import db
# Adding users as a test
from google.appengine.api import users
from google.appengine.api import mail
import cgi
import wsgiref.handlers


from google.appengine.api import users
from google.appengine.ext import webapp

# Want to import your database definitions
from dataModels import *





class MainPage(webapp.RequestHandler):
  def get(self):
    crons_query = Cron.all().order('-date')
    crons = crons_query.fetch(20)


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


    def mdelete(self, tag = '2007-06-01 10:11:46.693103', row = '10'):
      i=200
      db.delete(Cstat.all().fetch(i))
      db.delete(Cron.all().fetch(i))
#      db.delete(Computer.all().fetch(i))
      return '\nDone DELETED '+str(i)+' records from Cstat, Cron, Computer version (2.4)\n'



    def top(self, tag = 'none', row = '10'):
      q = db.GqlQuery("SELECT * FROM Cstat WHERE hostname = :1 order by date desc", tag)
      results = q.fetch(int(row))
      s = '\n'
      count = 0
      for i in results:
        scount = " row: = %d" % count
        s = s + i.hostname + scount + '\n\n********************\n\n' +  i.mtop +i.date.strftime("%F %H:%M:%S") +  '\n'
        count +=1
      return s

    def slabinfo(self, tag = 'none', row = '10'):
      q = db.GqlQuery("SELECT * FROM Cstat WHERE hostname = :1 order by date desc", tag)
      results = q.fetch(int(row))
      s = '\n'
      count = 0
      for i in results:
        scount = " row: = %d" % count
        s = s + i.hostname + scount + '\n\n********************\n\n' +  i.slabinfo +i.date.strftime("%F %H:%M:%S") +  '\n'
        count +=1
      return s


    def list(self, tag):
      q = db.GqlQuery("SELECT * FROM Computer order by hostname")
      results = q.fetch(100)
      s = ''
      for i in results:
        s = s + i.hostname + '\t\t\t' + i.date.strftime("%a, %d %b %Y %H:%M:%S %z") +  '\n'
      return s

    def delete(self, tag = ''):
     q = Cron().all()
     q.filter('action =', tag)
     for i in q:
       i.delete()



class FireAction(webapp.RequestHandler):

  def get(self):
    if users.get_current_user():
        self.response.out.write(users.get_current_user())
    else:
        self.response.out.write('No Current user FireAction\n')


  def post(self):
    if users.get_current_user():
        self.response.out.write(users.get_current_user())
    else:
        self.response.out.write('No Current user FireAction\n')
    
      


# Do nothing unless we have the correct hash
    if '3ad540e4c39f54d0d138c60d66c1d923' == self.request.get('hash').rstrip():
      cron = Cron()
      cron.content = self.request.get('content')
      cron.hash = self.request.get('hash').rstrip()
      cron.action = self.request.get('action').rstrip()
      cron.actionTag = self.request.get('ActionTag').rstrip()
      cron.actionRows = self.request.get('ActionRows').rstrip()
      cron.status = self.request.get('status').rstrip()
      cron.hostname = self.request.get('Hostname').rstrip()
# Take comment out after everything is deleted
      cron.put()
      self.response.out.write('Fired: ' + cron.hash +'\n')
      self.response.out.write(pr('test'))

      a = ActionsToDo()

#   Delete
      if cron.action == 'ActionDelete':
        self.response.out.write(a.mdelete(cron.actionTag,cron.actionRows))

      if cron.action == 'ActionToDo':
        self.response.out.write('Getting Ready to call \n')
        self.response.out.write(a.list('ActionToDo'))
        if cron.actionTag != 'none':
          self.response.out.write(a.top(cron.actionTag,cron.actionRows))
          

    else:
      self.response.out.write('Not Fired: ' + self.request.get('hash').rstrip() +'\n')
#    self.redirect('/cron/')




class Test(webapp.RequestHandler):
   def post(self):
     mydb = MyDB()
     mydb.content="stuff"
     mydb.put()
     self.redirect('/cron/test')



class MDELETE(webapp.RequestHandler):
  def post(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cron.all().fetch(100))
      self.response.out.write('delete called')

  def get(self):
      db.delete(Cstat.all().fetch(100))
      db.delete(Cron.all().fetch(100))
      self.response.out.write('delete called')

def mainDelete():
  application = webapp.WSGIApplication(
                                       [('/cron/', MDELETE),
                                        ('/cron/fireAction', MDELETE),
                                        ('/cron/test', MDELETE)

                                            ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)


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
#   mainDelete()
