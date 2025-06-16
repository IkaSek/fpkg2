#include "../API.h"
#include <stdlib.h>

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