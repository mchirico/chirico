#!/usr/bin/env ruby
5.times { print "One, Two"}
printf "\nmore\n" + `date`
prc = lambda { |name| puts "Hello, " + name }
prc.call "one!"

