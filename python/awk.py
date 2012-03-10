#!/usr/bin/env python
#  Created by Mike Chirico mchirico@gmail.com
#
#    
"""
Example of using ssh to call an awk program.



"""



import os,time,sys,signal,getopt


# Globals


# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)


def runcmd(N,CMD):
#    scmd='ssh -t '+N+' <<EOF\n'+str(CMD) +'\nEOF 2>/dev/null'
    scmd='ssh -t '+N+' '+str(CMD) +' 2>/dev/null'
    f=os.popen(scmd)
    m=f.readlines()
    f.close()
    return m

            

def findlock(N):
    a=[]
    pre=0
    post=1
    count=0
    for i in N:
        pre=count-1
        post=count+1
        count=count+1
        if i.find('Global Enqueue Services Deadlock detected') == 0:
            try:
                x,y,z=N[pre].strip(),i.strip(),N[post].strip()
                a.append([x,y,z])
                print x
                print y
                print z
                print
            except:
                print "Error in findlock"
    return a




def main():
    scmd=""" awk "/$(date -d '-1 day'  "+%a %b %d")/,EOF "'{printf("%s\\n",\$0)}' /u01/app/oracle/diag/rdbms/orcl/orcl/trace/alert_orcl.log """
    m=runcmd('big',scmd)
    a=findlock(m)



if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main()    
       
        




