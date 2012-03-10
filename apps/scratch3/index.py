import cgi
import wsgiref.handlers

from google.appengine.api import users
from google.appengine.ext import db
from google.appengine.ext import webapp
from google.appengine.ext.webapp import template

from google.appengine.ext.db import djangoforms

class Item(db.Model):
  name = db.StringProperty()
  quantity = db.IntegerProperty(default=1)
  target_price = db.FloatProperty(required=True)
  priority = db.StringProperty(default='Medium',choices=[
    'High', 'Medium', 'Low'])
  popularity = db.StringProperty(default='Popular',choices=[
    'Very Popular', 'Popular', 'Not Popular', 'Never Used', 'Dangerous'])
  shipping_cost = db.FloatProperty(required=True)
  entry_time = db.DateTimeProperty(auto_now_add=True)
  added_by = db.UserProperty()

class ItemForm(djangoforms.ModelForm):
  class Meta:
    model = Item
    exclude = ['added_by']


class MainPage(webapp.RequestHandler):
  def get(self):
    self.response.out.write('<html><body>'
                            '<form method="POST" '
                            'action="/">'
                            '<table>')
    # This generates our shopping list form and writes it in the response
    self.response.out.write(ItemForm())
    self.response.out.write('</table>'
                            '<input type="submit">'
                            '</form></body></html>')


  def post(self):
    data = ItemForm(data=self.request.POST)
    if data.is_valid():
      # Save the data, and redirect to the view page
      entity = data.save(commit=False)
      entity.added_by = users.get_current_user()
      entity.put()
      self.redirect('/items.html')
    else:
      # Reprint the form
      self.response.out.write('<html><body>'
                              '<form method="POST" '
                              'action="/">'
                              '<table>')
      self.response.out.write(data)
      self.response.out.write('</table>'
                              '<input type="submit">'
                              '</form></body></html>')



class ItemPage(webapp.RequestHandler):
  def get(self):
    query = db.GqlQuery("SELECT * FROM Item ORDER BY name")
    for item in query:
      self.response.out.write('<a href="/edit?id=%d">Edit</a> - ' %
                              item.key().id())
      self.response.out.write("%s - Need to buy %d, cost $%0.2f each, %s, %s, $%0.2f shipping<br>" %
                              (item.name, item.quantity, item.target_price,
                               item.priority, item.popularity, item.shipping_cost))



class EditPage(webapp.RequestHandler):
  def get(self):
    id = int(self.request.get('id'))
    item = Item.get(db.Key.from_path('Item', id))
    self.response.out.write('<html><body>'
                            '<form method="POST" '
                            'action="/edit">'
                            '<table>')
    self.response.out.write(ItemForm(instance=item))
    self.response.out.write('</table>'
                            '<input type="hidden" name="_id" value="%s">'
                            '<input type="submit">'
                            '</form></body></html>' % id)

  def post(self):
    id = int(self.request.get('_id'))
    item = Item.get(db.Key.from_path('Item', id))
    data = ItemForm(data=self.request.POST, instance=item)
    if data.is_valid():
      # Save the data, and redirect to the view page
      entity = data.save(commit=False)
      entity.added_by = users.get_current_user()
      entity.put()
      self.redirect('/items.html')
    else:
      # Reprint the form
      self.response.out.write('<html><body>'
                              '<form method="POST" '
                              'action="/edit">'
                              '<table>')
      self.response.out.write(data)
      self.response.out.write('</table>'
                              '<input type="hidden" name="_id" value="%s">'
                              '<input type="submit">'
                              '</form></body></html>' % id)





def main():
  application = webapp.WSGIApplication(
                                       [('/', MainPage),
                                        ('/edit', EditPage),
                                        ('/items.html', ItemPage),
                                        ],
                                       debug=True)

  wsgiref.handlers.CGIHandler().run(application)



if __name__=="__main__":
  main()
