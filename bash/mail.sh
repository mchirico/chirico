#!/bin/bash
# Days until Saturday
d_toSat=$((6- $(date "+%u") ))

# Days until Sunday
d_toSun=$((7- $(date "+%u") ))


Saturday=$(date -d "$d_toSat day" "+%B %d, %Y")
Sunday=$(date -d "$d_toSun day" "+%B %d, %Y")

echo  "
This is a reminder that the Raiser's Edge 7 application will be unavailable on 
Sunday, $Sunday between the hours of 6:00 A.M. and 12:00 P.M..  This 
outage is required to install the latest set of required patches from the vendor.

Please be sure to exit the system and save all work by 11:55 P.M. Saturday, $Saturday

The upgrade will be pulled down to your workstations upon logging in to the system 
for the first time, after the scheduled completion time.  Any users, who experience 
ODBC connection problems after the upgrade, please follow the following steps to 
correct the problem:

  Press the start button on your workstation
  Select Run
  When the Run dialog box appears, enter \\\charleston\re7_deploy\re7.vbs then press enter.
  Select \"OK\" for any messages that appear.
  Attempt to log back in to the Raiser's Edge system.

If you continue to experience problems connecting after following these steps 
please contact Mike Salvadore at extension 3-0491.

If you have any questions concerning this patch, please contact 
Eric Richardson at extension 3-8773

Thank you for your attention and cooperation in this matter.
"





