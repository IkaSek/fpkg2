#ifndef __API_H__
#define __API_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define FPKG_VERSION 00000100LL     /* 0.0.1-alpha */
#define FPKG_API_VERSION 16062025LL /* 16.06.2025 */
#define FPKG_API_PUBLIC __attribute__((visibility("default")))
#define FPKG_API_PRIVATE __attribute__((visibility("hidden")))
#define FPKG_API_EXTRN extern
#define FPKG_API_INLN inline

typedef long long INT;
typedef unsigned long long UINT;

typedef unsigned char UCHAR;

typedef float FLOAT32;
typedef long double FLOAT64;

FPKG_API_PUBLIC UINT API_min(UINT a, UINT b);
FPKG_API_PUBLIC UINT API_max(UINT a, UINT b);
FPKG_API_PUBLIC UINT API_nearest_pow2(UINT a);
FPKG_API_PUBLIC UINT API_floor(FLOAT64 a);
FPKG_API_PUBLIC UINT API_ceil(FLOAT64 a);

#define FN_PTR(tp, name) tp(*name)
typedef FN_PTR(int, API_AsRoot_callback)(void *);

/**
 * @brief Initializes the AsRoot module.
 *
 * This function sets up the necessary state for using the AsRoot functionality.
 *
 * @return 0 on success, non-zero error code otherwise
 */
FPKG_API_PUBLIC int API_AsRoot_init();
/**
 * @brief Calls a user-provided callback as root with the provided argument.
 *
 * This function attempts to execute the given callback in an elevated context,
 * passing the provided argument along. If successful, the function returns 0;
 * otherwise, it returns the error code associated with the failure.
 *
 * @param cb The callback to be executed as root
 * @param arg Argument to pass to the callback
 * @return 0 on success, non-zero error code otherwise
 */
FPKG_API_PUBLIC int API_AsRoot(API_AsRoot_callback cb, void *arg);

#define NOT ~
#define AND &
#define OR |
#define XOR ^

typedef FN_PTR(void *, API_IAllocator_Alloc)(size_t, void *);
typedef FN_PTR(void, API_IAllocator_Free)(void *, void *);

typedef struct API_IAllocator API_IAllocator;
struct API_IAllocator {
  API_IAllocator_Alloc alloc;
  API_IAllocator_Free free;

  void *ctx;
};

FPKG_API_PRIVATE static const API_IAllocator libc_alloc = {
    (API_IAllocator_Alloc)malloc, (API_IAllocator_Free)free, .ctx = NULL};

typedef struct API_Arena API_Arena;
struct API_Arena {
  struct __Page *pages;
};

FPKG_API_PUBLIC void *API_Arena_alloc(size_t s, API_Arena *a);
FPKG_API_PUBLIC void *API_Arena_realloc(API_Arena *a, void *p, size_t olds,
                                        size_t s);
FPKG_API_PUBLIC void API_Arena_destroy(API_Arena *a);

typedef struct API_ByteArray API_ByteArray;
struct API_ByteArray {
  size_t blen;
  size_t bmax;
  void **buf;
};

FPKG_API_PUBLIC void API_ByteArray_push(API_ByteArray *ba, void *data);
FPKG_API_PUBLIC void API_ByteArray_pop(API_ByteArray *ba);
FPKG_API_PUBLIC void API_ByteArray_free(API_ByteArray *ba);
FPKG_API_PUBLIC API_ByteArray API_ByteArray_dup(const API_ByteArray ba,
                                                API_IAllocator alloc);
FPKG_API_PUBLIC void API_ByteArray_sort(API_ByteArray *ba);

FPKG_API_PUBLIC size_t API_ucstrlen(const UCHAR *s);
FPKG_API_PUBLIC UCHAR *API_ucstrdup(API_IAllocator ialloc, const UCHAR *s);
FPKG_API_PUBLIC int API_ucstrcmp(const UCHAR *s1, const UCHAR *s2);
FPKG_API_PUBLIC UCHAR *API_ucstrcpy(UCHAR *restrict dest, size_t dest_len,
                                    const UCHAR *restrict src);
FPKG_API_PUBLIC size_t API_ucnstrlen(const UCHAR *s);

#endif