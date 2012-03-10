#!/usr/bin/env python
#  Created by Mike Chirico 
#
import os,time,sys,signal,getopt,popen2,re



p=re.compile('[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9] [0-9][0-9]\:[0-9][0-9]\:[0-9][0-9]')
p1=re.compile('unavailable')
p2=re.compile('Response Message\:Product\=[A-Z|a-z|_]*')
#productTime=1313526600000, size=539728
p3=re.compile('productTime\=[0-9]*')
p4=re.compile('size\=[0-9]*')


# Globals


# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)

# Runs ssh command
def runcmd(N,len=0):
    scmd=N
    r,w,e = popen2.popen3(scmd)
    m=r.readlines()
    e.readlines()
    r.close()
    e.close()
    w.close()
    return [os.getpid(),m]
            


def example_usage():
    s=""" Example usage
             -f file
             --file file
             """
    print s



def myparse():
    h={}
    opts=[]
    args=0
    try: opts,args=getopt.getopt(sys.argv[1:],'hf:',
              ['file='])
    except Exception, e:
        example_usage()
        return
    if len(opts) == 0:
        example_usage()
        return
    for o, a in opts:
        h[o]=a
    return h

                        
# Example Call                        
# get_log('tfsvr617','/opt/swim/logs/ExtSwimServices_')
def get_log(server,log = '/opt/swim/logs/ExtSwimServices_'):
    scmd="ssh %s 'ls -ltra %s*.xml|tail  -n1'" % (server,log)
    m=runcmd(scmd)
    log_file=m[1][0].split()[-1]
    return log_file


def pr_times(N):
    for i in N:
        k=p.search(i)
        k2=p2.search(i)
        if k:
            last_time=k.group()
        if k2:
            k1=p1.search(i)   # All the not founds
            if k1:
                continue
            else:
                tmp=i.split()
                productTime=p3.search(i)
                size=p4.search(i)
                if productTime:
                    if size:
                      print "%s %s %8d %s" % (last_time,productTime.group().replace('productTime=','')
                                                ,int(size.group().replace('size=',''))
                                                , k2.group().replace('Response Message:Product=',''))




def pr_footer(server,log_file):
    print "\nssh %s \"tail -n20 %s\" 2>/dev/null" % (server,log_file)       

def main(n):
    server='tfsvr617'
    dir='/opt/swim/logs/ExtSwimServices_'
    log_file=get_log(server,dir)
    scmd="""ssh %s 'grep -C3 "CIWS Response Message:" %s ' """ % (server,log_file)
    m=runcmd(scmd)
    pr_times(m[1])

    pr_footer(server,log_file)




if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main(sys.argv)    
       
        




