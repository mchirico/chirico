#!/bin/bash

# ALL
BACKUP0=/work/jboss/jbossPortal/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/backup/ 
mkdir -p ${BACKUP0}
for mdir in admin-console.war jmx-console.war cluster ROOT.war
do

    if [ -d ${BACKUP0}/${mdir} ]; then
	rm -rf "${MDEPLOY}/${mdir}"
    else
	mv ${MDEPLOY}/${mdir} ${BACKUP0}
    fi
done


# default
BACKUP0=/work/jboss/jbossPortal/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/backup/ 
MDEPLOY=/work/jboss/jbossPortal/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/deploy/ 
mkdir -p ${BACKUP0}
for mdir in admin-console.war jmx-console.war ROOT.war
do

    if [ -d ${BACKUP0}/${mdir} ]; then
	rm -rf "${MDEPLOY}/${mdir}"
    else
	mv ${MDEPLOY}/${mdir} ${BACKUP0}
    fi
done

# web
BACKUP0=/work/jboss/jbossPortal/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/web/backup/ 
MDEPLOY=/work/jboss/jbossPortal/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/web/deploy/ 
mkdir -p ${BACKUP0}
for mdir in jmx-console.war ROOT.war
do

    if [ -d ${BACKUP0}/${mdir} ]; then
	rm -rf "${MDEPLOY}/${mdir}"
    else
	mv ${MDEPLOY}/${mdir} ${BACKUP0}
    fi
done
