#!/usr/bin/env python


import cx_Oracle
db=cx_Oracle.connect('hr/garbo23@localhost:1521/orcl2')
print db.version
cur=db.cursor()
cur.execute('select * from jobs')
for row in cur:
    print row




