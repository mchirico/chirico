#!/bin/bash
# Copyright (c) GPL 2009 by Mike Chirico  <mchirico@gmail.com>
#
# Fill in your password here
PASSWORD=somepasswd
DEST_BUSINESS=dest_business_dir
DEST_PASSWD=dest_passwd_dir
USER=user
SERVER=server
#
#
cd /home/chirico
#
# BUSINESS
tar -zcf - cwxstatBooks|openssl des3 -salt -k ${PASSWORD} | dd of=cwxstat_business.des3
#dd if=cwxstat_business.des3 |openssl des3 -d -k ${PASSWORD}|tar zxf -
export mdate=`date "+%m.%d.%Y"`
ssh ${USER}@${SERVER}  "cp ${DEST_BUSINESS}/cwxstat_business.des3  ${DEST_BUSINESS}/cwxstat_business.$mdate.des3"    
scp cwxstat_business.des3  ${USER}@${SERVER}:${DEST_BUSINESS}/cwxstat_business.des3
#
#
# PASSWORD
tar -zcf - passwords|openssl des3 -salt -k ${PASSWORD} | dd of=passwords.des3
ssh ${USER}@${SERVER}  "cp ${DEST_PASSWD}/passwords.des3  ${DEST_PASSWD}/passwords.$mdate.des3"    
scp passwords.des3  ${USER}@${SERVER}:${DEST_PASSWD}/passwords.des3
