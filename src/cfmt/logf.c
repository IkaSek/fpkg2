#include "API.h"
#include <cfmt.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

FPKG_API_PUBLIC INT cfmt_logf(const INT level, char *s, ...) {
  char *b;
  FILE *stdlevl;
  switch (level) {
  case CFMT_LOG_LEVEL_NOLOG:
    b = s;
    stdlevl = stdout;
    break;
  case CFMT_LOG_LEVEL_LOG:
    b = cfmt_tbprintf("[" CFMT_COLOR_BLINK_CYAN "::" CFMT_COLOR_RESET "] %s\n",
                      s);
    stdlevl = stdout;
    break;
  case CFMT_LOG_LEVEL_WRN:
    b = cfmt_tbprintf("[" CFMT_COLOR_BLINK_YELLOW "^" CFMT_COLOR_RESET "] %s\n",
                      s);
    stdlevl = stdout;
    break;
  case CFMT_LOG_LEVEL_ERR:
    b = cfmt_tbprintf("[" CFMT_COLOR_BLINK_RED "!" CFMT_COLOR_RESET "] %s\n",
                      s);
    stdlevl = stderr;
    break;
  case CFMT_LOG_LEVEL_CRIT:
    b = cfmt_tbprintf("[" CFMT_COLOR_BLINK_PURPLE "*" CFMT_COLOR_RESET "] %s\n",
                      s);
    stdlevl = stderr;
    break;
  default:
    unreachable(); /* We don't have any other cases, a level argument being
                      mismatched is unlikely*/
  }

  va_list ap;
  va_start(ap, s);

  vfprintf(stdlevl, b, ap);

  va_end(ap);

  return strlen(b) + 1;
}