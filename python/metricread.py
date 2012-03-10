#!/usr/bin/env python
"""


"""
import os,time,sys,signal,re,pickle

mdate = re.compile('^([0-9][0-9])\/([0-9][0-9])\/([0-9][0-9]) ([0-9][0-9])\:([0-9][0-9])\:([0-9][0-9])')
tell = -1

def signal_handler(signal, frame):
        sys.exit(0)



def stripJunk(n):
	s=n.replace("'","")
	s=s.replace("-","")
	s=s.replace(" ","")
	return s


def reformatDate(n):
	m=mdate.search(n)
	s=''
	if m:
		s='20'+m.group(3)+'-'+m.group(1)+'-'+m.group(2)+' '+m.group(4)+':'+m.group(5)+':'+m.group(6)
	return s
	
		

def stripTabS(n):
	s=n.replace("  "," ")
	s=s.replace("\t"," ")
	while(s.find("  ") != -1):
		s=s.replace("  "," ")
	s=s.replace("\n","")
	return s


def buildTables(H):
	f=open('buildMetricTables.sql','w')
	s=''
	for i in H.keys():
		s='create table IF NOT EXISTS '+str(i)+' (section ,date datetime'
		for j in range(0,int(H[i])):
			s=s+',f'+str(j)
		s=s+');\n'
		f.write(s)
		f.write(". separator ','\n")
		f.write(".import metricImp"+str(i)+" "+str(i)+"\n")
	f.close()
			       

def simpleParse(N):
	s=""
	section=""
	rawdata=""
	newdate=""
	SECTION={}
	fileH={}
	for i in N:
		if (i.find(" --") != -1 and i.find("-- ") != -1):
			section= stripJunk(i)
		else:
			rawdata=stripTabS(i)
			if ( len(rawdata) > 17 ):
				newdate=reformatDate(rawdata[0:17])
				if (SECTION.has_key(section)):
					tmp=len(rawdata[18:].split(" "))
					if (SECTION[section] < tmp ):
						SECTION[section]=tmp
				else:
					SECTION[section]=len(rawdata[18:].split(" "))
					fileH['metricImp'+str(section)]=open('metricImp'+str(section),'w')

					
				print section,"'"+newdate+"'",rawdata[18:]
				fileH['metricImp'+str(section)].write(section+",'"+newdate+"'")
				for ti in str(rawdata[18:]).split(" "):
					fileH['metricImp'+str(section)].write(","+ti)
				fileH['metricImp'+str(section)].write("\n")
				
				
	buildTables(SECTION)
	for i in fileH.keys():
		fileH[i].close()
	
		
	

"""
sqlite3 junk2.db < buildMetricTables.sql
. separator ','
.import metricImpFxaMetrics FxaMetrics
"""
def insertSqlite3(n='junk2.db'):
	filesToRedo=[]
	f=os.popen('sqlite3 '+str(n)+' < buildMetricTables.sql 2>&1')
	m=f.readlines()
	f.close()
	k=[i.strip() for i in m]
	for i in k:
		f=open(i.split()[0])
		m=f.readlines()
		f.close()
		f=open(i.split()[0],'w')
		for j in m:
			s=''
			for x in j.strip().split(','):
				f.write(s+str(x))
				s=','
			for y in range(len(j.strip().split(',')),int(i.split()[4])):
				f.write(',')
			f.write('\n')
		f.close()
		filesToRedo.append(i.split()[0])
	f=open('buildMetricRedo.sql','w')
	f2=open('buildMetricTables.sql','r')
	m=f2.readlines()
	f2.close()
	k2=[i.strip() for i in m]
	f.write(". separator ','\n")
	for i in k2:
		tmp=i.split()
		if (tmp[0] == '.import'):
			if tmp[1] in filesToRedo:
				f.write(str(i)+'\n')
	f.close()
	f=os.popen('sqlite3 '+str(n)+' < buildMetricRedo.sql 2>&1')
	m=f.readlines()
	f.close()



def openFile(n,tag='.you'):
	k=statsThisTime(tag)
	global tell
	f=open(n,'r')
	if (tag != '.you' and type(k).__name__=='list'):
		if ( k[1][1] == list(os.stat(k[0]))[1]):   # check inode
			f.seek(k[1][6])
	m=f.readlines()
	tell=f.tell()
	f.close()
	m=[i.strip() for i in m]
	return m


def statsThisTime(tag='.you'):
	m=0
	try:
		f=open('metricread.pkl'+str(tag),'rb')
		m=pickle.load(f)
		f.close()
	except:
		return 0
	return m



def statsForNextTime(n,tag='.you'):
	m=[n]
	m.append(list(os.stat(n)))
	f=open('metricread.pkl'+str(tag),'wb')
	pickle.dump(m,f)
	f.close()


def main(N):
	if len(sys.argv) > 1:
		simpleParse(openFile('metric.txt',sys.argv[1]))
		statsForNextTime('metric.txt',sys.argv[1])
	else:
		simpleParse(openFile('metric.txt'))
		statsForNextTime('metric.txt')
	

	
	

    


if __name__ == '__main__':
        signal.signal(signal.SIGINT, signal_handler)
        main(sys.argv)

