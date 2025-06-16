#include <API.h>
#include <stddef.h>
#include <stdlib.h>

FPKG_API_PUBLIC size_t API_ucstrlen(const UCHAR *s) {
  size_t len = 0;
  while (*s != '\0') {
    len++;
    s++;
  }
  return len;
}

FPKG_API_PUBLIC size_t API_ucnstrlen(const UCHAR *s) {
  return API_ucstrlen(s) + 1;
}

FPKG_API_PUBLIC UCHAR *API_ucstrdup(API_IAllocator ialloc, const UCHAR *s) {
  size_t len = API_ucstrlen(s);

  UCHAR *ret = ialloc.alloc(len + 1, ialloc.ctx);
  for (size_t i = 0; i < len; ++i) {
    ret[i] = s[i];
  }

  ret[len] = '\0';

  return ret;
}

FPKG_API_PUBLIC UCHAR *API_ucstrcpy(UCHAR *restrict dest, size_t dest_len,
                                    const UCHAR *restrict src) {
  size_t src_len = API_ucstrlen(src);
  size_t copy_len = API_min(src_len, dest_len - 1);

  for (size_t i = 0; i < copy_len; ++i) {
    dest[i] = src[i];
  }

  dest[dest_len] = '\0';
  return dest;
}

FPKG_API_PUBLIC int API_ucstrcmp(const UCHAR *s1, const UCHAR *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    s1++;
    s2++;
  }

  INTC res = *s1 - *s2;
  if (res < 0)
    return -1;
  else if (res > 0)
    return 1;
  else
    return 0;
}