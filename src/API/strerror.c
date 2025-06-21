#include <API.h>
#include <API_Errors.sp.h>

FPKG_API_PUBLIC const char *API_strerror(INT error_code) {
  switch (error_code) {
  case API_ERROR_OK:
    return API_ERROR_OK_STR;
  case API_ERROR_ALLOC:
    return API_ERROR_ALLOC_STR;
  case API_ERROR_INVALIDARGUMENT:
    return API_ERROR_INVALIDARGUMENT_STR;
  case API_ERROR_PLUGERROR:
    return API_ERROR_PLUGERROR_STR;
  case API_ERROR_NOTFOUND:
    return API_ERROR_NOTFOUND_STR;
  }
}