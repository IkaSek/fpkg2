#include <API.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/acl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>

FPKG_API_PUBLIC int FS_sfcp(char *from, char *to) {
  int from_fd = open(from, O_RDONLY);
  if (from_fd == -1) {
    fprintf(stderr, "\tFailed to copy %s->%s using sendfile(3): %s", from, to,
            strerror(errno));
    return -1;
  }

  struct stat st;
  fstat(from_fd, &st);

  int to_fd = open(to, O_WRONLY | O_CREAT);
  if (to_fd == -1) {
    fprintf(stderr, "\tFailed to copy %s->%s using sendfile(3): %s", from, to,
            strerror(errno));
    return -1;
  }

  sendfile(to_fd, from_fd, 0, st.st_size);
  chmod(to, st.st_mode);

  close(to_fd);
  close(from_fd);

  return 0;
}