#!/usr/bin/env ruby
require 'mathn'
p = Prime.new
 p.each { |k| print k,"\n"; break unless k < 3000}
