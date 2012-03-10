#!/usr/bin/env python
import sqlite
con = sqlite.connect(":memory:")
cur = con.cursor()
cur.execute("create table IF NOT EXISTS junk  (a int,b int, c int);")
for i in range(0,500):
    cur.execute("insert into junk values ("+str(i)+","+str(i+1)+","+str(i+2)+");")
cur.execute("select a from junk order by a desc limit -1,5; ")
print cur.fetchall()
cur.close()
con.commit()
con.close()
