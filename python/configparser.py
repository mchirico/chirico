#!/usr/bin/env python
# 
#  Ref: http://docs.python.org/library/configparser.html
import ConfigParser

config = ConfigParser.RawConfigParser()

config.add_section('Section1')
config.set('Section1', 'int', '15')
config.set('Section1', 'bool', 'true')
config.set('Section1', 'float', '3.1415')
config.set('Section1', 'baz', 'fun')
config.set('Section1', 'bar', 'Python')
config.set('Section1', 'foo', '%(bar)s is %(baz)s!')

f=open('example.cfg','wb')
config.write(f)
f.close()

# Reading
config = ConfigParser.RawConfigParser()
config.read('example.cfg')
float=config.getfloat('Section1','float')
int=config.getint('Section1','int')
print float + int

