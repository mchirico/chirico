#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#define MY_CONFIG "su"
static struct pam_conv conv = { misc_conv, NULL };


void Run_My_Big_Application( ) {
  printf("success\n");

}

int main(void)
{
  pam_handle_t *pamh;
  int result;
  struct passwd *pw;
  if ((pw = getpwuid(getuid( ))) == NULL)
    perror("getpwuid");
  else if ((result = pam_start(MY_CONFIG, pw->pw_name, &conv, &pamh)) != PAM_SUCCESS)
    fprintf(stderr, "start failed: %d\n", result);
  else if ((result = pam_authenticate(pamh, 0)) != PAM_SUCCESS)
    fprintf(stderr, "authenticate failed: %d\n", result);
  else if ((result = pam_acct_mgmt(pamh, 0)) != PAM_SUCCESS)
    fprintf(stderr, "acct_mgmt failed: %d\n", result);
  else if ((result = pam_end(pamh, result)) != PAM_SUCCESS)
    fprintf(stderr, "end failed: %d\n", result);
  else
    Run_My_Big_Application( );            /* Run your application code */

  return 1;
}


