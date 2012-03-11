#!/bin/bash
#15 * * * * /home/chirico/pingtest/cron_wrapper.sh >/dev/null 2>&1
source /home/chirico/.bash_profile
rm /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
cd /home/chirico/pingtest/wiki
svn update
cd /home/chirico/pingtest
echo -e '
= Summary: Comcast Problems =

' > /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
echo -e "{{{\n" >>  /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
./wstatcron.py >> /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
echo -e "}}}\n" >>  /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
echo -e '\n\n [http://chirico.googlecode.com/svn/trunk/bash/pingtest/] ' >> /home/chirico/pingtest/wiki/Comcast_current_summary.wiki 
cd /home/chirico/pingtest/wiki
svn update
svn commit -m "cron auto commit Comcast results"
