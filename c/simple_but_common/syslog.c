/* This is an example of a program that logs 
    messages.

    LOG_MAIL /var/log/maillog or
    take a look at /etc/syslog.conf

        

*/

#include <syslog.h>

int main(void)
{

  openlog("syslog: ",LOG_PID,LOG_SYSLOG);
  syslog(3, "syslog prog: test");
  closelog();
  return 0;

}
