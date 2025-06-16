#ifndef __FS_H__
#define __FS_H__

#include "API.h"
typedef int FSPERM;
typedef struct FS_Dir_Iter FS_Dir_Iter;

/**
 * Create multiple directories at once.
 *
 * @param path The path to create the directory at. Must be an absolute or
 * relative path.
 * @param perm The permissions to set for the newly created directory (in
 * octal).
 *
 * @return 0 on success, non-zero error code on failure
 */
FPKG_API_PUBLIC int FS_mkdirr(char *path, FSPERM perm);

/**
 * Initializes a new directory iterator.
 *
 * This function creates and returns a new directory iterator, which can be used
 * to iterate over the contents of a directory.
 *
 * @param path The path to the directory for which to create the iterator. If
 * the directory does not exist or is inaccessible, this function will return
 * NULL.
 *
 * @return A newly created directory iterator, or NULL if an error occurred.
 */
FPKG_API_PUBLIC FS_Dir_Iter *FS_Dir_Iter_init(const char *path);
/**
 * Advances the iterator to the next directory entry in the file system.
 *
 * This function locks the mutex associated with the iterator to prevent
 * concurrent access, and returns a pointer to the name of the next directory
 * entry. If there are no more entries to iterate over, it returns NULL.
 *
 * @param iter The FS_Dir_Iter instance to advance.
 *
 * @return A string containing the name of the next directory entry, or NULL if
 * no more entries exist.
 */
FPKG_API_PUBLIC char *FS_Dir_Iter_next(FS_Dir_Iter *iter);
/**
 * Closes and frees resources associated with the directory iterator.
 *
 * This function should be called when no longer using a directory iterator to
 * ensure that system resources are properly released. It is not necessary to
 * call this function manually, as the directory iterator will automatically
 * close and free its resources when it goes out of scope. Additionally, it will
 * be deallocated by the API_Arena_free function when it is called.
 */
FPKG_API_PUBLIC void FS_Dir_Iter_close(FS_Dir_Iter *iter);

FPKG_API_PUBLIC int FS_sfcp(char *from, char *to);
FPKG_API_PUBLIC void FS_mktempd(UCHAR *buf, size_t buf_max, size_t n);
#endif