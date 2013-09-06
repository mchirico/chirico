import webapp2
class MainPage(webapp2.RequestHandler):
  def get(self):
      self.response.headers['Content-Type'] = 'text/plain'
      self.response.out.write('Hello, webapp World!\nVersion3\n')
      self.response.out.write('Source:https://github.com/mchirico/chirico/tree/master/apps/23isprime.appspot.com_Python2.7')

app = webapp2.WSGIApplication([('/', MainPage)],
                              debug=True)
