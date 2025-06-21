#include "../API.h"
#include <stdlib.h>
#include <string.h>

#define BMAX_INIT 64
FPKG_API_PUBLIC void API_ByteArray_push(API_ByteArray *ba, void *data) {
  if (ba->bmax == 0) {
    ba->bmax = BMAX_INIT;
    ba->buf = malloc(sizeof(void *) * ba->bmax);
  }

  if (ba->blen == ba->bmax) {
    ba->bmax *= 2;
    ba->buf = realloc(ba->buf, sizeof(void *) * ba->bmax);
  }

  ba->buf[ba->blen++] = data;
}

FPKG_API_PUBLIC void API_ByteArray_pop(API_ByteArray *ba) {
  if (ba->blen == 0) {
    return;
  }

  ba->buf[ba->blen] = 0;
  ba->blen--;
}

FPKG_API_PUBLIC void API_ByteArray_free(API_ByteArray *ba) { free(ba->buf); }

FPKG_API_PRIVATE int __ByteArray_sort_compare(const void *a, const void *b) {
  void *pa = *(void *const *)a;
  void *pb = *(void *const *)b;
  return (pa > pb) - (pa < pb);
}

FPKG_API_PUBLIC void API_ByteArray_sort(API_ByteArray *ba) {
  qsort(ba->buf, ba->blen, sizeof(void *), __ByteArray_sort_compare);
}

FPKG_API_PUBLIC API_ByteArray API_ByteArray_dup(const API_ByteArray ba,
                                                API_IAllocator alloc) {
  API_ByteArray bclone = (API_ByteArray){.blen = ba.blen, .bmax = ba.bmax};
  bclone.buf = alloc.alloc(sizeof(void *) * ba.bmax, alloc.ctx);
  memcpy(bclone.buf, ba.buf, sizeof(void *) * ba.blen);

  return bclone;
}