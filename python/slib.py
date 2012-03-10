#!/usr/bin/env python
# Created by Mike Chirico mchirico@gmail.com
# Version 0.0.5
#
# Remote SCP command passing a password.
#
#   ssh server1 -L 22000:server2:22
#
#   scp -P 22000 -r user2@localhost:dscript .
#   ssh user2@localhost -p 22000
#
# Note: Use no host key checking, so that you
#      do not get prompted. But, realize you're not
#      able to check for man in the middle attacks with
#      this option.
#
#         StrictHostKeyChecking=no
"""
Example usage:

#!/usr/bin/env python
import os, time, sys
from slib import *

if __name__ == '__main__':
    s=S()

    s.setuhpld('mchirico','server','password','/tmp/log1.1','log1.1')
    s.setlgappend(0)

    a=['ntpq -pn']
    a.append('date')
    a.append('echo "test"')

    s.lcmd(a)
    s.scp('Extending_with_C','mchirico@server:.')






The following is an example of running a sudo command


#!/usr/bin/env python
import os, time, sys
from slib import *

if __name__ == '__main__':
    s=S()

    s.setuhpld('mchirico','soekris10','password1','/tmp/log1.2','log1.2')
# Need append on for this
    s.setlgappend(1)
    s.setprmpt(1)


    b=['ls -l>>/tmp/log1.2']
    b.append('chown mchirico.mchirico /tmp/log1.2')
    s.rsu('passwordSU',b)

    a=['date']
    s.lcmd(a)





Below is another example


#!/usr/bin/env python
import os, time, sys
from slib import *


def walk(user,host,password,supasswd):
    s=S()
    s.setuhpld(user,host,password,'/tmp/logarch.1','logarch.1')
    s.setlgappend(1)
    s.setprmpt(1)

    s.scp('oraclecrontab',str(user)+'@'+host+':/tmp/.')
    s.scp('rootcrontab',str(user)+'@'+host+':/tmp/.')
    s.scp('archiveLogs.env',str(user)+'@'+host+':/tmp/.')

    a=['crontab -l>/tmp/oraclecrontab.old']
    a.append('crontab /tmp/oraclecrontab')
    s.lcmd(a)

    b=['mv /etc/logrotate.conf /etc/logrotate.conf.dist']
    b.append('mv /etc/logrotate.d /etc/logrotate.d.dist')
    b.append('cp /opt/tfms/archive/logrotate.conf /etc/.')
    b.append('cp -r /opt/tfms/archive/logrotate.d /etc/.')
    b.append('cp /tmp/archiveLogs.env /opt/tfms/archive/archiveLogs.env')
    b.append('chown oracle.oinstall /opt/tfms/archive/archiveLogs.env')
    b.append('crontab -l>/tmp/rootcrontab.old')
    b.append('crontab /tmp/rootcrontab')
    s.rsu(supasswd,b)

if __name__ == '__main__':
    walk('oracle','server01','passwdOracle','passwdSu')
    walk('oracle','server02','passwdOracle','passwdSu')





"""

import os, time, sys

class S(object):
    def __init__(self,user="",password=""):
        self.USER=user
        self.PASS=password
        self.logcnt=0
        self.LGAPPEND=False
        self.PRMPT=False
    
    def version(self):
        self.h={}
        self.h['version']='0.0.4'
        self.h['comment']='Beta'
        return self.h


    def setprmpt(self,flag):
        if (flag >= 1):
            self.PRMPT=True
        else:
            self.PRMPT=False


    def setlgappend(self,flag):
        if (flag >= 1):
            self.LGAPPEND=True
        else:
            self.LGAPPEND=False

    def setpass(self,password):
        self.PASS=password

    def setuser(self,user):
        self.USER=user

    def sethost(self,host):
        self.HOST=host

    def setuhp(self,user,host,password):
        self.USER=user
        self.HOST=host
        self.PASS=password

    def setuhpld(self,user,host,password,log,logdest):
        self.USER=user
        self.HOST=host
        self.PASS=password
        self.LOGNAME=log
        self.LOGDEST=logdest
        self.NEWLG=1

    def setpuh(self,password,user,host):
        self.USER=user
        self.HOST=host
        self.PASS=password

    def setlog(self,log):
        self.LOGNAME=log

    def setlogdest(self,logdest):
        self.LOGDEST=logdest

    def pause(self,d=0.9):
        time.sleep(d)

    def lstosmi(self,n):
        s=""
        for i in n[0:-1]:
            s+=str(i)+";"
        s+=str(n[-1])
        return s

# Dlog = directory and log
    def lstosmiDlog(self,n,log):
        if (self.LGAPPEND == False):
            return self.lstosmiDlogn(n,log)
        s=""
        for i in n[0:-1]:
            s+=str(i)+" >>"+str(log)+";"
        s+=str(n[-1])+" >>"+str(log)
        return s

    def lstosmiDlogn(self,n,log):
        s=str(n[0]) +" >"+str(log)+";"
        if len(n) <= 1:
            return s
        for i in n[1:-1]:
            s+=str(i)+" >>"+str(log)+";"
        s+=str(n[-1])+" >>"+str(log)
        return s

    def rscp(self,pw,dir1,cmd):
        pid, fd = os.forkpty()
    # If Child; execute external process
        if pid == 0:
             os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no",dir1,]+cmd)
        else:
            self.pause()
            k=os.read(fd, 1000)
            count=0
            while k.find("password") < 0:
               self.pause()
               count+=1
               try:
                  k=os.read(fd, 1000)
               except:
                  return
               if count > 3:
                  return
            os.write(fd, pw + "\n")
            self.pause()
            k=os.read(fd, 1000)
            self.pause()
            res = ''
            print k
            return res

    def rcmde(self, user, rhost, pw, cmd):
        if (self.PRMPT == True):
              print cmd
        pid, fd = os.forkpty()
    # If Child; execute external process
        if pid == 0:
            os.execv("/usr/bin/ssh", ["/usr/bin/ssh", "-l", user,"-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no",rhost,"source ~/.bash_profile;"] +cmd)
        else:
            self.pause()
            k=os.read(fd, 1000)
            while k.find("password") < 0:
               self.pause()
               k=os.read(fd, 1000)
            os.write(fd, pw + "\n")
            self.pause()
            k=os.read(fd, 1000)
            self.pause()
            res = ''
            print k
            return res


    def su(self,pw,a):
        s=self.lstosmi(a)
        return self.sur(pw,s)


    def sur(self, pw, cmd):
        pid, fd = os.forkpty()
# This command is a string. Not a list.
        cmd=cmd.replace(';;',';')
# If Child; execute external process
        if pid == 0:
            os.execv("/bin/su", ["/bin/su", "-c",] +[str(cmd)])
        else:
            self.pause()
            k=os.read(fd, 1000)
            while k.find("assword") < 0:
               self.pause()
               k=os.read(fd, 1000)
            os.write(fd, pw + "\n")
            self.pause()
            k=os.read(fd, 1000)
            self.pause()
            res = ''
            print k
            return res



    def cmda(self,s,USER,PASS,HOST,LOGNAME,LOGDEST):
# Taking out...I think this is causing a problem.  
#        self.rcmde(str(USER), str(HOST), str(PASS), [str(s)+'>>'+LOGNAME])
        self.rcmde(str(USER), str(HOST), str(PASS), [str(s)])
        self.rscp(str(PASS),str(USER)+'@'+str(HOST)+':'+LOGNAME,[LOGDEST])


# This one requires the fill path to log
    def lcmd(self,a):
        s=self.lstosmiDlog(a,self.LOGNAME)
        if (self.LOGDEST==""):
           self.LOGDEST=self.LOGNAME
        self.cmda(s,self.USER,self.PASS,self.HOST,self.LOGNAME,self.LOGDEST)


    def rrscp(self,pw,dir1,cmd):
        pid, fd = os.forkpty()
    # If Child; execute external process
        if pid == 0:
             os.execv("/usr/bin/scp", ["scp","-o","StrictHostKeyChecking=no","-o","PubkeyAuthentication=no","-r",dir1,]+cmd)
        else:
            self.pause()
            k=os.read(fd, 1000)
            count=0
            while k.find("password") < 0:
               self.pause()
               count+=1
               try:
                  k=os.read(fd, 1000)
               except:
                  return
               if count > 3:
                  return
            os.write(fd, pw + "\n")
            self.pause()
            k=os.read(fd, 1000)
            self.pause()
            res = ''
            print k
            return res

    def scp(self,source,desc):
        return self.rrscp(self.PASS,source,[desc])


    def buildta(self,n):
        s="    a=['"+str(n[0])+"']\n"
        for i in n[1::]:
            s=s+"    a.append('"+str(i)+"')\n"
        return s

    def sufile(self,pw,a):
        s="""#!/usr/bin/env python
import os, time
from slib import *

if __name__ == '__main__':
    s=S()
"""
        s=s+self.buildta(a)
        s=s+"    s.su('"+str(pw)+"',a)\n"
        return s


    def rsu(self,pw,a):
        f=open("remote.py","w")
        f.write(self.sufile(pw,a))
        f.close()
        os.chmod('remote.py',0700)
        self.scp('remote.py',self.USER+"@"+self.HOST+":.")
        self.scp('slib.py',self.USER+"@"+self.HOST+":.")
        self.lcmd(['./remote.py'])

