#!/usr/bin/env python
def ask_ok(prompt, retries=4, complaint='Yes or no!'):
   while True:
       ok = raw_input(prompt)
       if ok in ('y', 'ye', 'yes'): return True
       if ok in ('n','no','nop', 'nope'): return False
       retries = retries -1
       if retries < 0: raise IOError, 'refusenik user'
       print complaint

if ask_ok("Would you like potatos?\n"):
    print ("Yeah, he said is want's potatoes\n")
else:
    print ("He said no\n")
