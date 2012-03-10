#!/bin/bash
MBASE="/home/chirico/dev/chirico/java/jboss"
cd /home/chirico/jboss
rm -rf jboss-5.1.0.GA-src
tar -xzf jboss-5.1.0.GA-src.tar.gz 
cd ./jboss-5.1.0.GA-src/build/
sh build.sh
cd /home/chirico/jboss/jboss-5.1.0.GA-src/build/
cp ${MBASE}/oracle-ds.xml /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/deploy/.
cp ${MBASE}/oracle-ds.xml /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/minimal/deploy/.
cp ${MBASE}/oracle-ds.xml /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/standard/deploy/.
cp ${MBASE}/oracle-ds.xml /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/web/deploy/.
cp ${MBASE}/oracle-ds.xml /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/deploy/.
cp /u01/app/oracle/product/11.1.0/db_1/sqldeveloper/jdbc/lib/ojdbc14.jar /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/lib/.
# ssl
cp ~/.keystore  /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/web/conf/chap8.keystore
cp ~/.keystore  /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/conf/chap8.keystore
cp ~/.keystore  /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/conf/chap8.keystore
cp ${MBASE}/server.xml   /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/web/deploy/jbossweb.sar/server.xml
cp ${MBASE}/Allserver.xml   /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/all/deploy/jbossweb.sar/server.xml
cp ${MBASE}/Dserver.xml   /home/chirico/jboss/jboss-5.1.0.GA-src/build/output/jboss-5.1.0.GA/server/default/deploy/jbossweb.sar/server.xml

