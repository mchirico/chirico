#!/usr/bin/env python
#  Tool to make is easier to grep though a running system
#  Created by:  mchirico@gmail.com
#  verson: 0.0.3
#  updated: 
#
import os,time,sys,signal,sqlite


def signal_handler(signal, frame):
    sys.exit(0)
              


def drop_g():
    con = sqlite.connect("g.sqlite")
    cur = con.cursor()
    cur.execute("drop table if exists hash_dir;")
    cur.close()
    con.commit()
    con.close()

def build_g(N):
    con = sqlite.connect("g.sqlite")
    cur = con.cursor()
    cur.execute("create table IF NOT EXISTS hash_dir  (h text,dir text);")
    for i in N:
        cur.execute("insert into hash_dir values ('"+str(i)+"','"+str(N[i])+"');")
    cur.close()
    con.commit()
    con.close()

def dbGrab():
    con = sqlite.connect("g.sqlite")
    cur = con.cursor()
    cur.execute("select h,dir from hash_dir")
    m=cur.fetchall()
    cur.close()
    con.commit()
    con.close()
    return m

def dbToH(m):
    h={}
    for i in m:
        h[i[0]]=i[1]
    return h

def H(N):
    h={}
    h['AppFltDst']='/opt/tfms/logs/AppFltDst/trace/AppFltDst_3_B4_29-TF.xml'
    h['AppFltIng']='/opt/tfms/logs/AppFltIng/trace/AppFltIng_3_B4_29-TF.xml'
    h['AppFltIng2']='/opt/tfms/logs/AppFltIng2/trace/AppFltIng2_3_B4_29-TF.xml'
    h['AppTmiFxaDmd']='/opt/tfms/logs/AppTmiFxaDmd/trace/AppTmiFxaDmd_3_B4_29-TF.xml'
    h['AppTmiFxaDmd2']='/opt/tfms/logs/AppTmiFxaDmd2/trace/AppTmiFxaDmd2_3_B4_29-TF.xml'
    h['AppTmiFxaDmd3']='/opt/tfms/logs/AppTmiFxaDmd3/trace/AppTmiFxaDmd3_3_B4_29-TF.xml'
    h['AppWxRpt']='/opt/tfms/logs/AppWxRpt/trace/AppWxRpt_3_B4_29-TF.xml'
    return h[str(N)]

def H2():
    h={}
    h['AppFltDst']='/opt/tfms/logs/AppFltDst/trace/AppFltDst_3_B4_29-TF.xml'
    h['AppFltIng']='/opt/tfms/logs/AppFltIng/trace/AppFltIng_3_B4_29-TF.xml'
    h['AppFltIng2']='/opt/tfms/logs/AppFltIng2/trace/AppFltIng2_3_B4_29-TF.xml'
    h['AppTmiFxaDmd']='/opt/tfms/logs/AppTmiFxaDmd/trace/AppTmiFxaDmd_3_B4_29-TF.xml'
    h['AppTmiFxaDmd2']='/opt/tfms/logs/AppTmiFxaDmd2/trace/AppTmiFxaDmd2_3_B4_29-TF.xml'
    h['AppTmiFxaDmd3']='/opt/tfms/logs/AppTmiFxaDmd3/trace/AppTmiFxaDmd3_3_B4_29-TF.xml'
    h['AppWxRpt']='/opt/tfms/logs/AppWxRpt/trace/AppWxRpt_3_B4_29-TF.xml'
    return h

def Portals(n):
    h={}
    h['tfsvr609']='/opt/tfms/logs/trace/faa_ss_3_B4_29-TF.xml'
    h['tfsvr610']='/opt/tfms/logs/trace/faa_ss_3_B4_29-TF.xml'
    h['tfsvr611']='/opt/tfms/logs/trace/faa_ss_3_B4_29-TF.xml'
    h['tfsvr612']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfsvr613']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfsvr614']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm1svr424']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm1svr425']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm1svr426']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm2svr424']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm2svr425']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm2svr426']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm3svr424']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm3svr425']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm3svr426']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm4svr424']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm4svr425']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    h['tfm4svr426']='/opt/tfms/logs/trace/ext_ss_3_B4_29-TF.xml'
    if str(n) in h:
        return h[str(n)]
    else:
        return 0



def fixstr(N):
    s=str(N)
    s=s.replace("[","[\'")
    s=s.replace("]","\']")
    s=s.replace(",","\',\'")
    return s



def buildscmd(N,tag=' 2>/dev/null'):
    cmd=""
    if len(N) < 4:
        return
    exec("servers="+fixstr(N[1]))
    exec("containers="+fixstr(N[2]))
    s=""
    cmd=""
    for i in servers:
        if Portals(i):
            s="ssh "+i+" \""+"grep "+N[3]+" "+Portals(i)+"\""+tag
            runcmd(s,len(N))
        else:
            s="ssh "+i+" \""+"grep "+N[3]+" "
            for j in containers:
                runcmd(s+H(str(j))+"\""+tag,len(N))


def figure_switch(len):
    if len == 4:
        return 1
    else:
        return 0


def runcmd(N,len=0):
    if figure_switch(len):
        f=os.popen(N)
        m=f.readlines()
        f.close()
        
        print "<g_prog=\"["+N+"]\"]>"
        for i in m:
            print i
        print "</g_prog=\"["+N+"]\"]>"
    else:
        print N



def build_dirs(n="AppTmiFxaDmd2"):
    cmd="""ls -tr /opt/tfms/logs/"""+str(n)+"""/trace/*xml*[0-9{4}\-0-9{2}\-1-2{2}$]|grep -vP 'quartz|Flight'"""
    ssh="ssh tfsvr723 \""+cmd+"\" 2>/dev/null"
    p=os.popen(ssh)
    m=p.readlines()
    p.close()
    m=[i.strip() for i in m]
    return m

def list_containers():
    n=['AppFltDst','AppFltIng','AppFltIng2','AppTmiFxaDmd','AppTmiFxaDmd2','AppTmiFxaDmd3','AppWxRpt']
    return n

def build_all_dirs():
    n=[]
    for i in list_containers():
        n.append(build_dirs(i))










def main(N,tag=' 2>/dev/null'):
    buildscmd(N,tag)


def main2(N,tag=' 2>/dev/null'):
    drop_g()
    build_g(H2())
    h=dbToH(dbGrab())
    print h


if __name__ == '__main__':
    signal.signal(signal.SIGINT, signal_handler)
    main2(sys.argv)
# Debug        
#        print "servers: " +sys.argv[1]
#        print "containers: "+sys.argv[2]
#        print "grep params: "+sys.argv[3]

       
        




