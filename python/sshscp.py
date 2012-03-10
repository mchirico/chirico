#!/usr/bin/env python
# Remote SCP command passing a password.
#
# Note: Use no host key checking, so that you
#      do not get prompted. But, realize you're not
#      able to check for man in the middle attacks with
#      this option.
#
#         StrictHostKeyChecking=no
import os, time

def pause(d=0.9):
    time.sleep(d)

def rcmd(pw,dir1,cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-r",dir1,]+cmd)
    else:
        pause()
        k=os.read(fd, 1000)
        count=0
        while k.find("password") < 0:
           pause()
           count+=1
           try:
              k=os.read(fd, 1000)
           except:
              return
           if count > 3:
              return
        os.write(fd, pw + "\n")
        pause()
        k=os.read(fd, 1000)
        pause()
        res = ''
        print k
        return res


rcmd('password','./.ssh', ['user@host:.'])


