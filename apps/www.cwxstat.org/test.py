import wsgiref.handlers

from google.appengine.ext import webapp

def intersect(s1,s2):
    res = []
    for x in s1:
      if x in s2:
         res.append(x)
    return res

k = "note"
p = "boat"


class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write('Hello, webapp World!')
    self.response.out.write('\n\n')
    self.response.out.write(intersect(k,p))

class Ping(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write('Hello, Ping!')

def main():
  application = webapp.WSGIApplication(
                                       [
                                        ('/test', MainPage),
                                        ('/test/', MainPage),
                                        ('/test.html', MainPage),
                                        ('/ping.html', Ping),

                                        ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()


