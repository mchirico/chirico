#!/usr/bin/env python
import sqlite3
con = sqlite3.connect("db")
cur = con.cursor()
cur.execute("create table IF NOT EXISTS junk  (a int,b int, c int);")
cur.execute("insert into junk values (1,2,8);")
cur.execute("insert into junk values (4,5,9);")
cur.execute("insert into junk values (4,5,19);")
a=4
b=5
cur.execute("select * from junk where a=? and b=?",(a,b))
print cur.fetchall()
cur.close()
con.commit()
con.close()
