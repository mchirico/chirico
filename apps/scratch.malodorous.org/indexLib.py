import os
import cgi
import wsgiref.handlers

from google.appengine.ext import webapp
from google.appengine.ext import db
from google.appengine.ext.webapp import template



# These are used for linking/ordering

class Library(db.Model):
    name = db.StringProperty()
    address = db.StringProperty()
    city = db.StringProperty()

    def books(self):
        return (x.book for x in self.librarybook_set)

class Book(db.Model):
    title = db.StringProperty()
    author = db.StringProperty()

    def libraries(self):
        return (x.library for x in self.librarybook_set)


class LibraryBook(db.Model):
    library = db.ReferenceProperty(Library)
    book = db.ReferenceProperty(Book)





class MainPage(webapp.RequestHandler):
  def get(self):



    # Setup libraries
    lib1 = Library(name='lib1', address='street a', city='city1') #, libscol=libs)
    lib2 = Library(name='lib2', address='street b', city='city2') #, libscol=libs)
    lib1.put()
    lib2.put()


    book1 = Book(title='book1', author='author one') #, bookscol=books)
    book1.put()
    book2 = Book(title='book2', author='author one') #, bookscol=books)
    book2.put()
    book3 = Book(title='book1', author='author two') #, bookscol=books)
    book3.put()
    book4 = Book(title='book2', author='author two') #, bookscol=books)
    book4.put()
    book5 = Book(title='book3', author='author two') #, bookscol=books)
    book5.put()


    l1 = LibraryBook(library=lib1, book=book1)
    l2 = LibraryBook(library=lib1, book=book2)
    l3 = LibraryBook(library=lib1, book=book4)
    l4 = LibraryBook(library=lib2, book=book4)
    l5 = LibraryBook(library=lib2, book=book5)
    l6 = LibraryBook(library=lib2, book=book3)
    l7 = LibraryBook(library=lib2, book=book1)
    l1.put()
    l2.put()
    l3.put()
    l4.put()
    l5.put()
    l6.put()
    l7.put()



    template_values= {
            'lib': lib1.name,
            'books_at_lib': lib1.books(),
            'forbook': book1.title,
            'libs_by_book': book1.libraries(),
            'libs_books': Library.all().order('name'),
            'books_libs': Book.all().order('-author').order('title'),
            }
    path = os.path.join(os.path.dirname(__file__), 'index.html')
    self.response.out.write(template.render(path, template_values))




def main():
    application = webapp.WSGIApplication(
                                       [('/', MainPage)],
                                       debug=True)
    wsgiref.handlers.CGIHandler().run(application)

if __name__ == "__main__":
    main()
