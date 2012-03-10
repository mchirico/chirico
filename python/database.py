<<<<<<< .mine
#!/usr/bin/env python
#  
#
#    
import os,time,sys,signal,getopt


# Globals


# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)

# Runs ssh command

def runcmd(server,login,sql,len=0):
    scmd="""ssh %s "source ~/.bash_profile;sqlplus -s %s <<EOF\n %s EOF " 2>/dev/null""" % (server,login,sql) 
    f=os.popen(scmd)
    m=f.readlines()
    f.close()
    return m



def mclean(n):
    a=[]
    for i in n:
        try:
            print(i.replace('\n',''))
            a.append(i.replace('\n',''))
        except:
            print "issue on append in mclean"
    return  a

            

def config(server,login,param):
    sql="""
set echo off
set feedback off
set linesize 1000
set pagesize 1000
set trimspool on
set verify off
alter session set nls_date_format = 'YYYY-MM-DD HH24:MI:SS';
alter session set nls_timestamp_format ='YYYY-MM-DD HH24:MI:SS';
column ftext format A50
column arrive format A20
column lock_ts format A20

column originating_source format A10
column creation_tm format A20
column route_start_pt format A8
column route_stop_pt format A8

select table_name,tablespace_name, user_stats from user_tables where rownum < %s;


exit;
"""    % param
    return (server,login,sql)



def msetup(server,login,sql):
    print server
    mclean(runcmd(server,login,sql))
    print
    print



def main(param=1):

    server="big"
    login="chirico/mike"
    server,login,sql = config(server,login,param)
    msetup(server,login,sql)






if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main(8)
"""
    if len(sys.argv) <= 1:
         print "Need to enter some variable"
         print sys.argv[0] + " 19370457"
         sys.exit(1)
    else:
         main(sys.argv[1])    
       
        
"""




=======
#!/usr/bin/env python
"""
 Created by Mike Chirico mchirico@gmail.com


 Program to ssh into an Oracle database server,
 assuming you have ssh keys setup. This does not
 require any Oracle drivers.
 

 This program assumes you have created the following
 table, populating it with data.


 create table python_test (a int, b clob, c date);
 insert into python_test (a,b,c) values (0,'sample data',sysdate);
 insert into python_test (a,b,c) values (1,'2nd row',sysdate);
 insert into python_test (a,b,c) values (1,'3rd row',sysdate);


"""
import os,time,sys,signal,getopt


# Globals


# Ctl-c will catch and exit
def signal_handler(signal, frame):
    sys.exit(0)

# Runs ssh command

def runcmd(server,login,sql,len=0):
    scmd="""ssh %s "source ~/.bash_profile;sqlplus -s %s <<EOF\n %s EOF " 2>/dev/null""" % (server,login,sql) 
    f=os.popen(scmd)
    m=f.readlines()
    f.close()
    return m



def mclean(n):
    a=[]
    for i in n:
        try:
            print(i.replace('\n',''))
            a.append(i.replace('\n',''))
        except:
            print "issue on append in mclean"
    return  a

            

def config(server,login):
#
#
    sql="""
set echo off
set lines 232
set pages 66
set trimspool on
set verify off
alter session set nls_date_format = 'YYYY-MM-DD HH24:MI:SS';                    
alter session set nls_timestamp_format ='YYYY-MM-DD HH24:MI:SS';     
COLUMN b      HEADING 'b' FORMAT A20


select a,b,c from python_test;


exit;
"""    
    return (server,login,sql)



def msetup(server,login,sql):
    print server
    mclean(runcmd(server,login,sql))
    print
    print



def main():
# Assuming you have ssh keys setup to computer big
# Assuming Oracle username: chirico
#                 password: mike
#                 sid: orcl
    server="big"
#    login="chirico/mike@orcl"
    login="chirico/mike"
    server,login,sql = config(server,login)
    msetup(server,login,sql)






if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main()    
       
        




>>>>>>> .r2908
