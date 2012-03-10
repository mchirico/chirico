from google.appengine.ext import db

#---------------------------------------------------------
#       Databases
#---------------------------------------------------------

#The following is for Metric

#------ SHARDS ------
# Ref: http://code.google.com/appengine/articles/sharding_counters.html
import random

class SimpleCounterShard(db.Model):
    """Shards for the counter"""
    count = db.IntegerProperty(required=True, default=0)

NUM_SHARDS = 20

def get_count():
    """Retrieve the value for a given sharded counter."""
    total = 0
    for counter in SimpleCounterShard.all():
        total += counter.count
    return total

def increment():
    """Increment the value for a given sharded counter."""
    def txn():
        index = random.randint(0, NUM_SHARDS - 1)
        shard_name = "shard" + str(index)
        counter = SimpleCounterShard.get_by_key_name(shard_name)
        if counter is None:
            counter = SimpleCounterShard(key_name=shard_name)
        counter.count += 1
        counter.put()
    db.run_in_transaction(txn)




class Reroute_Total(db.Model):
	mdate = db.DateTimeProperty()
	summary = db.StringProperty()
	count = db.IntegerProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)


class Queue(db.Model):
	mdate = db.DateTimeProperty()
	queue = db.StringProperty()
	name = db.StringProperty()
	ready = db.IntegerProperty()
	wait = db.IntegerProperty()
	avg = db.FloatProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)

class Accumulator(db.Model):
    counter = db.IntegerProperty()
    



class Summary(db.Model):
	author = db.UserProperty()
	blob_key = db.StringProperty()
	summary = db.StringProperty()
	heart = db.IntegerProperty()
	start = db.DateTimeProperty()
	stop = db.DateTimeProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)
	pt = db.GeoPtProperty()


class ParsedPts(db.Model):
	author = db.UserProperty()
	blob_key = db.StringProperty()
	rec = db.IntegerProperty()
	alt = db.FloatProperty()
	t_alt = db.FloatProperty()
	dist  = db.FloatProperty()
	t_dist  = db.FloatProperty()
	heart = db.IntegerProperty()
	content = db.StringProperty(multiline=True)
	date = db.DateTimeProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)
	pt = db.GeoPtProperty()

class Qsummary(db.Model):
	author = db.UserProperty()
	blob_key = db.StringProperty()
	rec = db.IntegerProperty()
	alt = db.FloatProperty()
	t_alt = db.FloatProperty()
	dist  = db.FloatProperty()
	t_dist  = db.FloatProperty()
	heart = db.IntegerProperty()
	content = db.StringProperty(multiline=True)
	date = db.DateTimeProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)
	pt = db.GeoPtProperty()


class MyDebug(db.Model):
	author = db.UserProperty()
	blob_key = db.StringProperty()
	content = db.StringProperty(multiline=True)
	date = db.DateTimeProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)
	pt = db.GeoPtProperty()

class User(db.Model):
	author = db.UserProperty()
	userid = db.StringProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)
	


class EntryIndex(db.Model):
	author = db.UserProperty()
	blob_key = db.StringProperty()
	content = db.StringProperty(multiline=True)
	date = db.DateTimeProperty()
	lock_ts = db.DateTimeProperty(auto_now_add=True)

