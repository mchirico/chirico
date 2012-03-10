#!/usr/bin/env python
import sqlite
con = sqlite.connect("db")
cur = con.cursor()
cur.execute("create table IF NOT EXISTS junk  (a int,b int, c int);")
cur.execute("insert into junk values (1,2,8);")
cur.execute("insert into junk values (4,5,9);")
cur.execute("insert into junk values (4,5,19);")
a=4
b=5
cur.execute("select * from junk where a="+str(a)+" and b="+str(b))
print cur.fetchone()
cur.close()
con.commit()
con.close()
