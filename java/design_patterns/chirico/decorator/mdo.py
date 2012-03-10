#!/usr/bin/env python
import sys,os
cmd="javac DogTestDrive.java"
cmdg="java DogTestDrive"
rs=os.popen(cmd).read()
if (rs == ''):
    rs=os.popen(cmdg).read()
    print rs



os.popen(cmd).read().find('running')
