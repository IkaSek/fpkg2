#include <API.h>
#include <string.h>

FPKG_API_PUBLIC char *API_cslib_strdup(API_IAllocator alloc, char *s) {
  char *news = alloc.alloc(strlen(s) + 1, alloc.ctx);
  strcpy(news, s);
  return news;
}