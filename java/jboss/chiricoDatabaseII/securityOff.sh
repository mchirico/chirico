#!/bin/bash

# All
BACKUP0=/home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/backup/
MALL=/home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/deploy/
mkdir -p ${BACKUP0}
for mdir in admin-console.war jmx-console.war cluster ROOT.war
do

    if [ -d ${MALL}/${mdir} ]; then
	echo "Directory Exists"
    else
	cp -r ${BACKUP0}/${mdir} ${MALL}/.
    fi
done


# Default
BACKUP0=/home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/backup/
MDEFAULT=/home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/deploy/
mkdir -p ${BACKUP0}
for mdir in admin-console.war jmx-console.war ROOT.war
do

    if [ -d ${MDEFAULT}/${mdir} ]; then
	echo "Directory Exists"
    else
	cp -r ${BACKUP0}/${mdir} ${MDEFAULT}/.
    fi
done

