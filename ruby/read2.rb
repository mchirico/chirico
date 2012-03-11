#!/usr/bin/env ruby

# Create a hash from reading in a file

h=Hash[*File.read('f.txt').split(/[, \n\r]+/)]
printf("h[\"john\"]=%s \n\n", h["john"])
#
#
h.each do |key, value|
  printf("%s  %s\n",key,value);
end



