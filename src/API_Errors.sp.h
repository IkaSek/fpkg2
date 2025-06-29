#ifndef __API_ERRORS_H__
#define __API_ERRORS_H__

#include <API.h>
#define API_ERROR_OK_STR "Ok"
#define API_ERROR_ALLOC_STR "Alloc"
#define API_ERROR_INVALIDARGUMENT_STR "InvalidArgument"
#define API_ERROR_PLUGERROR_STR "PlugError"
#define API_ERROR_INVALIDPERMISSIONS_STR "InvalidPermissions"
#define API_ERROR_NOTFOUND_STR "NotFound"
enum API_Error {
  API_ERROR_OK = 0,
  API_ERROR_ALLOC = 1,
  API_ERROR_INVALIDARGUMENT = 2,
  API_ERROR_PLUGERROR = 3,
  API_ERROR_INVALIDPERMISSIONS = 4,
  API_ERROR_NOTFOUND = 5
};

FPKG_API_PUBLIC const char *API_strerror(INT error_code);
#endif
