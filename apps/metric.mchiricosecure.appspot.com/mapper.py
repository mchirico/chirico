from mapreduce import operation as op
from models import *

def process(entity):
  # change entity
  yield op.db.Put(entity)



def addCountryToVisitedPlace(entity):
  count = Count()
  count.count = 1
  count.Put()

  queryplaces = Place.all()
  queryplaces.filter('gid = ', str(entity.geoId))
  places = queryplaces.fetch(1)
  if len(places) > 0:
    place = places[0]
    entity.country = place.country
    yield op.db.Put(entity)



def testReduce(entity):
  count2 = Count2()
  count2.count = entity.count
  count2.put()
  yield op.counters.Increment("counter1")
  if entity.count == 1:
    entity.count = entity.count + 1
    yield op.db.Put(entity)
  else:
    entity.count = entity.count + 10
    yield op.db.Put(entity)


