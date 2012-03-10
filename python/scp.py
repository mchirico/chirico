#!/usr/bin/env python
#!/usr/bin/env python
#Remote command through SSH using user/password
#ssh -l root  -o StrictHostKeyChecking=no
import os, time

def pause(d=0.9):
    time.sleep(d)

def rcmd(pw, cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
#         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-r","file1","user@host:file2"])
         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-r","test",]+cmd)
    else:
        pause()
        k=os.read(fd, 1000)
        print k
        pause()
        os.write(fd, pw + "\n")
        pause()
        k=os.read(fd, 1000)
        pause()
        res = ''
        print k
        return res


rcmd('password', ['user@hostdest:.'])


