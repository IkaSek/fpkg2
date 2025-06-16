#include "../API.h"
#include "../FS.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <threads.h>

FPKG_API_PUBLIC int FS_mkdirr(char *path, FSPERM perm) {
  char *dir = path;
  while (*dir != '\0') {
    if (*dir == '/') {
      *dir = '\0';
      if (mkdir(dir, perm) != 0 && errno != EEXIST) {
        fprintf(stderr, "\tError creating directory: %s\n", path);
        return -1;
      }
      *dir = '/';
    }
    dir++;
  }
}