from google.appengine.ext import db
from google.appengine.ext import search

##################################################################################
#                                                                                #
#                       Models                                                   #
#                                                                                #
##################################################################################

class VisitedPlace(db.Model):
  geoId = db.IntegerProperty()
  name = db.StringProperty()
  country = db.StringProperty()
  lat = db.StringProperty()
  lon = db.StringProperty()
  pubDate = db.DateTimeProperty(auto_now_add=True)
  userId = db.IntegerProperty()
  review = db.TextProperty()
  reviewPubDate = db.DateTimeProperty(auto_now_add=True)
  comments = db.IntegerProperty()



class Place(db.Model):
  gid = db.StringProperty()
  name = db.StringProperty()
  ascii = db.StringProperty()
  alternate = db.StringListProperty()
  lat = db.StringProperty()
  lon = db.StringProperty()
  fclass = db.StringProperty()
  fcode = db.StringProperty()
  country = db.StringProperty()
  cc2 = db.StringProperty()
  admin1 = db.StringProperty()
  admin2 = db.StringProperty()
  admin3 = db.StringProperty()
  admin4 = db.StringProperty()
  population = db.StringProperty()
  elevation = db.StringProperty()
  gtopo30 = db.StringProperty()
  timezone = db.StringProperty()
  visitors = db.IntegerProperty()
  reviews = db.IntegerProperty()



class Count(db.Model):
  count = db.IntegerProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

class Count2(db.Model):
  count = db.IntegerProperty()
  lock_ts = db.DateTimeProperty(auto_now_add=True)

