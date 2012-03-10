import wsgiref.handlers
from google.appengine.ext import webapp



class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    key="""
$ gpg --fingerprint mchirico@cwxstat.com
pub   1024D/3E146185 2008-07-27
      Key fingerprint = CC94 A085 6FAC 369A 65F8  4526 4F62 FD7A 3E14 6185
uid                  Mike Chirico (www.cwxstat.com) <mchirico@cwxstat.com>
sub   2048g/704C7D0C 2008-07-27
"""
    self.response.out.write(key)

def main():
  application = webapp.WSGIApplication(
                                       [
                                        ('/gpg', MainPage),
                                        ('/gpg/', MainPage),
                                        ('/pgp', MainPage),
                                        ('/pgp/', MainPage),
                                        ],
                                       debug=True)
  wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
  main()


