#!/usr/bin/env python
#Remote command through SSH using user/password
#ssh -l root  -o StrictHostKeyChecking=no
import os, time

def pause(d=0.9):
    time.sleep(d)

def rcmd(user, rhost, pw, cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
        os.execv("/usr/bin/ssh", ["/usr/bin/ssh", "-l", user,"-o","StrictHostKeyChecking=no", rhost] +cmd)
    else:
        pause()
        k=os.read(fd, 1000)
        while k.find("password") < 0:
           pause()
           k=os.read(fd, 1000)
        os.write(fd, pw + "\n")
        pause()
        k=os.read(fd, 1000)
        pause()
        res = ''
        print k
        return res


if __name__ == '__main__':
#   rcmd('mchirico', 'cluster0', 'password', [' ps auxf > /tmp/mout;w>>/tmp/mout'])
#   rcmd('mchirico', 'cluster0', 'password', [' sqlplus chirico/mike @test.sql > /tmp/sql.txt'])
#   rcmd('mchirico', 'cluster0', 'password', ['source ~/.bash_profile;sqlplus chirico/mike @test.sql>/tmp/junk.txt'])
#    rcmd('mchirico', 'cluster0', 'password', ['source ~/.bash_profile;cd /home/mchirico/dev/java/ant/example_w_manifest/;./set.env;ant'])

