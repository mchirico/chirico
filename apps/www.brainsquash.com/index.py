import os
import thread
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template
from google.appengine.ext import db
from google.appengine.api import urlfetch
from google.appengine.ext.webapp.util import run_wsgi_app
import cgi
import wsgiref.handlers


class Student(db.Model):
  age = db.IntegerProperty()
  fn = db.StringProperty()
  ln = db.StringProperty()
  tag = db.StringProperty()


class Course(db.Model):
  room = db.StringProperty()
  building = db.StringProperty()
  title = db.StringProperty()
  time = db.StringProperty()

class StudentCourse(db.Model):
  skey = db.ReferenceProperty(Student)
  ckey = db.ReferenceProperty(Course)




class Pr(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write('test')


class Sql(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    self.response.out.write("select * from jobs where min_salary>='&1'\n/\n")


class SignIN(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/html'
    s="""
<html>
<head></head>
<body>
<a href=http://www.brainsquash.com/comments.html>comments</a>


<!-- Include the Google Friend Connect javascript library. -->
<script type="text/javascript" src="http://www.google.com/friendconnect/script/friendconnect.js"></script>

<!-- Define the div tag where the gadget will be inserted. -->
<div id="div-1228593036593" style="width:282px;border:1px solid #cccccc;"></div>
<!-- Render the gadget into a div. -->
<script type="text/javascript">
var skin = {};
skin['BORDER_COLOR'] = '#cccccc';
skin['ENDCAP_BG_COLOR'] = '#e0ecff';
skin['ENDCAP_TEXT_COLOR'] = '#333333';
skin['ENDCAP_LINK_COLOR'] = '#0000cc';
skin['ALTERNATE_BG_COLOR'] = '#ffffff';
skin['CONTENT_BG_COLOR'] = '#ffffff';
skin['CONTENT_LINK_COLOR'] = '#0000cc';
skin['CONTENT_TEXT_COLOR'] = '#333333';
skin['CONTENT_SECONDARY_LINK_COLOR'] = '#7777cc';
skin['CONTENT_SECONDARY_TEXT_COLOR'] = '#666666';
skin['CONTENT_HEADLINE_COLOR'] = '#333333';
skin['ALIGNMENT'] = 'right';
google.friendconnect.container.setParentUrl('/' /* location of rpc_relay.html and canvas.html */);
google.friendconnect.container.renderSignInGadget(
 { id: 'div-1228593036593',
   site: '01081394706655418391'},
  skin);
</script>
</body>
</html>
"""
    self.response.out.write(s)




    



class Test(webapp.RequestHandler):
  def get(self):
    s0 = Student(age=17,fn='Bob',ln='Anderson',tag='37N9')
    s0.put()

    s1 = Student(age=44,fn='Susan',ln='Chirico',tag='B1T')
    s1.put()

    s2 = Student(age=44,fn='Michael',ln='Chirico',tag='B2T')
    s2.put()
  
    c0 = Course(room='102',building='Mendal',title='Accounting')
    c0.put()

    c1 = Course(room='103',building='Mendal',title='Calculus 101')
    c1.put()

    c2 = Course(room='104',building='Mendal',title='Calculus 101')
    c2.put()



    sc0 = StudentCourse(skey=s0,ckey=c0)
    sc0.put()

    sc1 = StudentCourse(skey=s1,ckey=c0)
    sc1.put()

    sc2 = StudentCourse(skey=s2,ckey=c1)
    sc2.put()

    sc2 = StudentCourse(skey=s2,ckey=c2)
    sc2.put()

    self.response.headers['Content-Type'] = 'text/plain'
    s='you hit test\n'
    self.response.out.write(s)

class TestHtml(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s='you hit test.html\n'
    self.response.out.write(s)


class D(webapp.RequestHandler):
  def get(self):
    a=[1,2,4]
    template_values = {
      'array': a,
      }
    path = os.path.join(os.path.dirname(__file__), 'dindex.html')
    self.response.out.write(template.render(path, template_values))

class T(webapp.RequestHandler):
  def get(self):

    exec("a=[1,2,3,4,5,6,7,8,9]")
    url='t'
    url_linktext='mikechirico'
    result = urlfetch.fetch('http://mikechirico.com/test')
    template_values = {
      'array': a,
      'result': result.content,
      'url': url,
      'url_linktext': url_linktext,
      }

    path = os.path.join(os.path.dirname(__file__), 'index.html')
    self.response.out.write(template.render(path, template_values))


class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.headers['Content-Type'] = 'text/plain'
    s=range(1,20)
    self.response.out.write(s)

application = webapp.WSGIApplication(
                                     [('/', SignIN),
                                      ('/test',Test),
                                      ('/test.html',TestHtml),
                                      ('/t',T),
                                      ('/d',D),
                                      ('/pr',Pr),
                                      ('/sql',Sql),
                                      ('/sql.txt',Sql),
                                      ],
                                     debug=True)

def main():
  run_wsgi_app(application)

if __name__ == "__main__":
  main()
