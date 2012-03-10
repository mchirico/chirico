import wsgiref.handlers
from google.appengine.ext import db
from google.appengine.ext import webapp

class Heading(db.Model):
  id = db.IntegerProperty()
  url = db.StringProperty(multiline=True)
  content = db.StringProperty(multiline=True)
  date = db.DateTimeProperty(auto_now_add=True)

class BodyData(db.Model):
  id = db.IntegerProperty()
  content = db.StringProperty(multiline=True)
  date = db.DateTimeProperty(auto_now_add=True)


class Setup(webapp.RequestHandler):
  def get(self):
     heading = Heading()
     bodyData = BodyData()

     heading.id=0
     heading.content = 'Home'
     heading.url = '<a href=www.cwxstat.com>'
     heading.put()

     bodyData.id=0
     bodyData.content = 'Example Content'
     bodyData.put()

     self.redirect('/')



class MainPage(webapp.RequestHandler):
  def get(self):
    bodyData = db.GqlQuery("SELECT * FROM BodyData ORDER BY date DESC LIMIT 10")


    self.response.headers['Content-Type'] = 'text/plain'
    for row in bodyData:
      self.response.out.write(row.content)
    self.response.out.write('Hello, webapp World!')

def main():
  application = webapp.WSGIApplication(
                                       [('/', MainPage),('/setup',Setup)],
                                       debug=True)

  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()
