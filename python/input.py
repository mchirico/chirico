#!/usr/bin/env python
"""
    ./input.py
    Enter python command > r=23
    Enter python command > print r+3
    Enter python command >
    

"""
while 1:
    cmd = raw_input('Enter python command >')
    if not cmd:
        break
    exec(cmd)
