#!/usr/bin/env python
#  Created by Mike Chirico
#  version 0.0.6tf
#    
"""

You'll need to setup cron for this.

35 * * * * /home/sysadmin/bin/kill_three.py

Consider the following problems

a. What happens if the container is down
b. Need to log each step (Done)
c. Clean up some of the functions to only do one thing
d. It is nosy running. (Improved)
-- kill log files may grow, since data may get appended.
e. There is NEVER a cleanup for logs written. How long are we doing this?

"""



import os,time,sys,signal,getopt,datetime


# Globals
LOG="/tmp/killthree."+datetime.datetime.now().strftime("%Y.%m.%d.%A.%H.%M.%S")
DIR="/home/sysadmin/bin/logs_kill3"
LAB='tf'

# Make me generic
def logcleanup():
    scmd="""find /tmp  -cmin +1440 -iname 'killthree.*' -exec rm -f {} \; 2>/dev/null"""
    try:
        f=os.popen(scmd)
        m=f.readlines()
        f.close()
    except:
        log("problem with logcleanup()")


def log(n):
    f=open(LOG,'a')
    f.write(datetime.datetime.now().strftime("%Y.%m.%d (%A) %H:%M:%S")+": ")
    f.write(str(n))
    f.write('\n')
    f.close()




# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)


def runcmd(N,CMD):
    #    scmd='ssh  '+N+' <<EOF\n'+str(CMD) +'\nEOF 2>/dev/null'
    scmd='ssh  '+N+' "'+str(CMD) +'" 2>/dev/null'
    log(scmd)
    try:
        f=os.popen(scmd)
        m=f.readlines()
        f.close()
    except:
        log("Error in runcmd: >"+scmd+"<")
        return false
    return m



            

def msplit(N):
    process_k3=['OC4J:AppTmiFxaDmd3','OC4J:AppTmiFxaDmd2','OC4J:AppTmiFxaDmd','OC4J:AppWxRpt','OC4J:AppFltDst','OC4J:AppFltIng2','OC4J:AppFltIng']
    A=[]
    for i in N:
        j=i.split('|')
        if len(j) == 2:
            a=j[0].rstrip().lstrip()
            b=j[1].rstrip().lstrip()
            if a in process_k3:
                A.append("kill -3 %s" % b)
    return A



#
# Creates the dir to put the logs in.
def makelogdir(DIR):
    scmd="mkdir -p "+str(DIR)
    f=os.popen(scmd)
    m=f.readlines()
    f.close()




#
#
#     
def grabfile(N,server):
    t=datetime.datetime.now()
    mdate=t.strftime('%Y-%m-%d-%H.%M.%S')
    makelogdir(DIR)
    a=[]
    scmd=""
    for i in N:
        i=i.strip()
        jfile=i[i.rfind('/')+1::]
        scmd="""scp %s:%s %s/%s.%s.%s  2>/dev/null""" % (server,i,DIR,server,jfile,mdate)
        a.append(scmd)
    for i in a:
       log(i)
       f=os.popen(i)
       m=f.readlines()
       f.close()



# What will you do if the container is not up?
def runkill_list(server,N):
    scmd=""
    for i in N:
#        print "runkill_list  server",server,"  i ",i
        runcmd(server,i) 




def kill_three_main(server):
    print "Server: ",server
    scmd="""/opt/oracle/product/10.1.3.4/J2ee/opmn/bin/opmnctl status -noheaders -fmt %prt18%pid7R"""
    m=runcmd(server,scmd)
    lst_kill=msplit(m)
    runkill_list(server,lst_kill)
    scmd="""find /opt/oracle/product/10.1.3.4/J2ee/opmn/logs  -cmin -4 -iname 'default_group*.log'"""
    k=runcmd(server,scmd)
# It is possible k will not return anything...kill did not work or file too old
    grabfile(k,server)




def main():
    logcleanup()
    servers=[]
    for i in range(723,727):
        servers.append(LAB+str('svr')+str(i))
    for i in servers:
        kill_three_main(i)
        



if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main()    
       
        




