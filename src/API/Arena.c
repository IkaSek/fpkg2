#include <API.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define API_INITIAL_PAGE_SIZE (4096)
#define API_GROWTH_FACTOR_BS 1

struct __Page {
  void *data;
  size_t len;
  size_t max;
  struct __Page *next;
};

FPKG_API_PUBLIC void *API_Arena_alloc(size_t s, API_Arena *a) {
  if (a->pages == NULL) {
    a->pages = malloc(sizeof(struct __Page));
    a->pages->data = mmap(NULL, API_INITIAL_PAGE_SIZE, PROT_WRITE | PROT_READ,
                          MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    a->pages->len = 0;
    a->pages->max = API_INITIAL_PAGE_SIZE;
  }

  struct __Page *p = a->pages;
  size_t prevmax = 0;
  while (p != NULL) {
    if (p->len + s > p->max) {
      void *ptr = (void *)((char *)p->data + p->len);
      p->len += s;

      return ptr;
    }
    prevmax = p->max;
    p = p->next;
  }

  p = malloc(sizeof(struct __Page));
  size_t pg_len = API_max(prevmax << API_GROWTH_FACTOR_BS, API_nearest_pow2(s));
  p->data = mmap(NULL, pg_len, PROT_WRITE | PROT_READ,
                 MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  p->len += s;
  p->max = pg_len;
  return p->data;
}

FPKG_API_PUBLIC void *API_Arena_realloc(API_Arena *a, void *p, size_t olds,
                                        size_t s) {
  void *newp = API_Arena_alloc(s, a);
  memcpy(newp, p, olds);
  return newp;
}

FPKG_API_PUBLIC void API_Arena_destroy(API_Arena *a) {
  struct __Page *cursor = a->pages;
  struct __Page *next;
  while (cursor != NULL) {
    munmap(cursor->data, cursor->max);
    next = cursor->next;
    free(cursor);
    cursor = next;
  }
}