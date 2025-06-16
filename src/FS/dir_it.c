#include "../API.h"
#include "../FS.h"
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/stat.h>

struct FS_Dir_Iter {
  pthread_mutex_t mtx;
  char *parent_path;
  DIR *parent_dir;

  char *curr;
};

FPKG_API_PUBLIC FS_Dir_Iter *FS_Dir_Iter_init(const char *path) {
  FS_Dir_Iter *iter = malloc(sizeof(FS_Dir_Iter));
  if (iter == NULL)
    return NULL;
  iter->parent_path = strdup(path);
  if (iter->parent_path == NULL)
    return NULL;

  iter->parent_dir = opendir(path);
  iter->mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
  iter->curr = ".";

  return iter;
}

FPKG_API_PUBLIC char *FS_Dir_Iter_next(FS_Dir_Iter *iter) {
  pthread_mutex_lock(&iter->mtx);

  struct dirent *entry;

  free(iter->curr);

  if ((entry = readdir(iter->parent_dir)) != NULL) {
    char *name = strdup(entry->d_name);
    if (name == NULL)
      return NULL;

    iter->curr = name;

    pthread_mutex_unlock(&iter->mtx);

    return name;
  }

  closedir(iter->parent_dir);
  iter->parent_dir = NULL;
  pthread_mutex_unlock(&iter->mtx);

  return NULL;
}

FPKG_API_PUBLIC void FS_Dir_Iter_close(FS_Dir_Iter *iter) {
  pthread_mutex_destroy(&iter->mtx);
  free(iter->parent_path);
}