#!/usr/bin/env ruby


# Create/append the file and add data
f = File.open("data.txt","a")
f.print "This is some data to add\n"
f.close


t = Thread.new do
  File.read("data.txt")
end
print t.value


