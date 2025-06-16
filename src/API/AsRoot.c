#include "../API.h"

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

FPKG_API_PRIVATE pam_handle_t *G_pam_hndl = NULL;
FPKG_API_PUBLIC int API_AsRoot_init() {
  if (getuid() == 0)
    return 0;
  pam_start("LOGIN", "root", NULL, &G_pam_hndl);
  if (G_pam_hndl == NULL)
    return -1;

  printf("Some functionality requires root privileges.\n");
  printf("Please enter your password to continue.\n");
  int auth_res = pam_authenticate(G_pam_hndl, 0);
  if (auth_res != PAM_SUCCESS)
    return -1;

  return 0;
}
int API_AsRoot(API_AsRoot_callback cb, void *arg) {
  int ret;
  if (getuid() == 0) {
    ret = cb(arg);
    return ret;
  }

  setuid(0);
  ret = cb(arg);
  setuid(getuid());
  return ret;
}