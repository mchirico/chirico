#!/usr/bin/env python
# Remote SCP command passing a password.
#
# This is designed to work with Python 2.3.4
#
#   ssh server1 -L 22000:server2:22
#
#   scp -P 22000 -r user2@localhost:dscript .
#   ssh -o StrictHostKeyChecking=no user2@localhost -p 22000
#
# Note: Use no host key checking, so that you
#      do not get prompted. But, realize you're not
#      able to check for man in the middle attacks with
#      this option.
#
#         StrictHostKeyChecking=no
"""
Example usage:

import os, time, sshlib

if __name__ == '__main__':
    USER='User1'
    PASS='PassWord'
    HOST='server'

    
    s='source ~/.test_env;echo $TESTENV'
    sshlib.cmd(s,USER,PASS,HOST)
    s='ps auxf'
    sshlib.cmd(s,USER,PASS,HOST)

# Or
    a=['source ~/.test_env','echo $TESTENV','ps auxf']
    sshlib.lcmd(a,USER,PASS,HOST,"/tmp/sshtest.log.1","sshtest.log.1")

# Note this run's the scp -r command
    sshlib.scp(PASS,"file1","user@server:/tmp/.")

"""



import os, time

logcnt=0


def pause(d=0.9):
    time.sleep(d)

#
# List to 
def lstosmi(n):
    s=""
    for i in n[0:-1]:
        s+=str(i)+";"
    s+=str(n[-1])
    return s

# Dlog = directory and log
def lstosmiDlog(n,log):
    s=""
    for i in n[0:-1]:
        s+=str(i)+" >>"+str(log)+";"
    s+=str(n[-1])+" >>"+str(log)
    return s


def rscp(pw,dir1,cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no",dir1,]+cmd)
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


def rcmd(user, rhost, pw, cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
        os.execv("/usr/bin/ssh", ["/usr/bin/ssh", "-l", user,"-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no",rhost] +cmd)
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


def rcmde(user, rhost, pw, cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
        os.execv("/usr/bin/ssh", ["/usr/bin/ssh", "-l", user,"-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no",rhost,"source ~/.bash_profile;"] +cmd)
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



#
#  Scp -r option
#
def rrscp(pw,dir1,cmd):
    pid, fd = os.forkpty()
# If Child; execute external process
    if pid == 0:
         os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no","-r",dir1,]+cmd)
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


def scp(pw,source,desc):
    return rrscp(pw,source,[desc])



def cmd(s,USER,PASS,HOST,LOGNAME='sshcmd.log.'):
    global logcnt
    logcnt+=1
    SecNan=os.popen('date "+%s.%N"').readline().strip('\n')
    
    if (LOGNAME == 'sshcmd.log.'):
        LOGNAME=SecNan+"."+USER+"."+HOST+".log."
    rcmde(str(USER), str(HOST), str(PASS), [str(s)+'>/tmp/'+LOGNAME+str(logcnt)])
    rscp(str(PASS),str(USER)+'@'+str(HOST)+':/tmp/'+LOGNAME+str(logcnt),[LOGNAME+str(logcnt)])


def cmda(s,USER,PASS,HOST,LOGNAME,LOGDEST):
    rcmde(str(USER), str(HOST), str(PASS), [str(s)+'>>'+LOGNAME])
    rscp(str(PASS),str(USER)+'@'+str(HOST)+':'+LOGNAME,[LOGDEST])


# This one requires the fill path to log
def lcmd(a,USER,PASS,HOST,LOGNAME='/tmp/sshcmd.log.1',LOGDEST=""):
    s=lstosmiDlog(a,LOGNAME)
    if (LOGDEST==""):
       LOGDEST=LOGNAME
    cmda(s,USER,PASS,HOST,LOGNAME,LOGDEST)















