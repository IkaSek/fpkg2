#include <API.h>
#include <assert.h>
#include <cfmt.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

FPKG_API_PRIVATE static thread_local char temp_buf[CFMT_TEMPBUF_SIZE];

FPKG_API_PUBLIC char *cfmt_tbprintf(const char *s, ...) {
  memset(temp_buf, 0, CFMT_TEMPBUF_SIZE);
  va_list ap;
  va_start(ap, s);

  UINT len = vsnprintf(NULL, 0, s, ap);
  assert(len < CFMT_TEMPBUF_SIZE - 1 && "vsnprintf overflow.");
  va_end(ap);
  va_start(ap, s);

  vsnprintf(temp_buf, CFMT_TEMPBUF_SIZE, s, ap);

  va_end(ap);

  return temp_buf;
}