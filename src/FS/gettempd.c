#include <API.h>
#include <FS.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FPKG_API_PUBLIC void FS_gettempd(char *buf, size_t buf_max, size_t n) {
  char chars[] = "abcdefghijklmnoprstquwxyz"
                 "ABCDEFGHIJKLMNOPRSTQUWXYZ"
                 "0123456789";
  time_t tm;
  time(&tm);
  srand(tm);

  snprintf(buf, buf_max -= sizeof("/tmp/"), "/tmp/");
  char *buf_next = buf + sizeof("/tmp/");

  for (size_t i = 0; i < n; ++i) {
    if (buf_max == 0) {
      buf_next[i] = '\0';
      break;
    }
    buf_next[i] = chars[rand() % sizeof(chars)];
    buf_max--;
  }

  *(char *)((uintptr_t)buf_max + n) = '\0';
}