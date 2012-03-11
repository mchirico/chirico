#!/usr/bin/env ruby
require 'rubygems'
require 'sqlite3'

db = SQLite3::Database.new("test.db")
db.execute("drop table if exists junk")
db.execute("create table junk (a int,b varchar(20))")
db.execute("insert into junk (a,b) values (1,'Line one')")
db.execute("insert into junk (a,b) values (2,'Line two')")
rows = db.execute("select * from junk")
puts rows.size # two rows
p rows
#
#p rows[0].size  # There are two columns
print rows[0][0]," ", rows[1][1],"\n"


