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


def rscp(pw,dir1,cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no",dir1]+cmd)
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


# This is the routine that creates the exec string. You'll want to modify
def svrcmd():
    a=[]
    b=[]
    password='P3ssw0rd'
    for i in range(1,10):
          s="rcmd('root', 'tttwks0"+str(i)+"', '"+str(password)+"', ['ntpq -pn>/tmp/ntpq.log'])"
          a.append(s)
          s="rscp('"+str(password)+"','root@tttwks0"+str(i)+":/tmp/ntpq.log', ['tttwks0"+str(i)+"ntpq.log'])"
          b.append(s)
    for i in range(10,81):
          s="rcmd('root', 'tttwks"+str(i)+"', '"+str(password)+"', ['ntpq -pn>/tmp/ntpq.log'])"
          a.append(s)
          s="rscp('"+str(password)+"','root@tttwks"+str(i)+":/tmp/ntpq.log', ['tttwks"+str(i)+"ntpq.log'])"
          b.append(s)
    return [a,b]



"""
# Use this to check your work

z=svrcmd()

for i in range(0,80):
    print z[0][i]


for i in range(0,80):
    print z[1][i]



"""




if __name__ == '__main__':
#   The following is for single commands:    
#     rcmd('root', 'tttwks01', 'P3ssw0rd', ['ntpq -pn>/tmp/ntpq.log'])
#     rscp('P3ssw0rd','root@tttwks01:/tmp/ntpq.log', ['tttwks01ntpq.log'])
#   Below, this will run all
      z=svrcmd()
      for i in range(0,len(z[0])):
          exec z[0][i]
          exec z[1][i]



