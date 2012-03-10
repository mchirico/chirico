#!/usr/bin/env python

"""
 drop table if exists animals;

  create table animals (
    name varchar(10),
    legs tinyint);

  insert into animals (name, legs) values ('owl', 2);
  insert into animals (name, legs) values ('dog', 4);
  insert into animals (name, legs) values ('ant', 6);
  insert into animals (name, legs) values ('tick', 8);
  insert into animals (name, legs) values ('pentapus', 5);


"""

import MySQLdb
conn = MySQLdb.connect(user = "admin1", db = "python", passwd = "s3cr3tpass45")
cursor = conn.cursor()


cursor.execute("drop table if exists animals")
cursor.execute("create table animals(name varchar(10), legs tinyint)")
cursor.execute("insert into animals (name, legs) values ('owl', 2)")
cursor.execute("insert into animals (name, legs) values ('dog', 4)")
cursor.execute("insert into animals (name, legs) values ('ant', 6)")
cursor.execute("insert into animals (name, legs) values ('tick', 8)")
cursor.execute("insert into animals (name, legs) values ('pentapus', 5)")


num_rows = cursor.execute("SELECT name, legs FROM animals ORDER BY legs")
print num_rows, "rows returned"

row = cursor.fetchone()
while row != None:
      print row
      row = cursor.fetchone()

print

  # fetch all at once, ordered by name
cursor.execute("SELECT name, legs FROM animals ORDER BY name")
rows = cursor.fetchall()
for r in rows:
      print r

cursor.close ()
conn.close ()




    
