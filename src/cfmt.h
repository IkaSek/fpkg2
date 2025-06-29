#ifndef __CFMT_H__
#define __CFMT_H__

#include <API.h>

#define CFMT_TEMPBUF_SIZE 4096

#define CFMT_LOG_LEVEL_NOLOG 0
#define CFMT_LOG_LEVEL_LOG 1
#define CFMT_LOG_LEVEL_WRN 2
#define CFMT_LOG_LEVEL_ERR 3
#define CFMT_LOG_LEVEL_CRIT 4

#define CFMT_COLOR_RED "\e[0;31m"
#define CFMT_COLOR_GREEN "\e[0;32m"
#define CFMT_COLOR_YELLOW "\e[0;33m"
#define CFMT_COLOR_BLUE "\e[0;34m"
#define CFMT_COLOR_PURPLE "\e[0;35m"
#define CFMT_COLOR_CYAN "\e[0;36m"
#define CFMT_COLOR_WHITE "\e[0;37m"

#define CFMT_COLOR_BLINK_RED "\e[0;91m"
#define CFMT_COLOR_BLINK_GREEN "\e[0;92m"
#define CFMT_COLOR_BLINK_YELLOW "\e[0;93m"
#define CFMT_COLOR_BLINK_BLUE "\e[0;94m"
#define CFMT_COLOR_BLINK_PURPLE "\e[0;95m"
#define CFMT_COLOR_BLINK_CYAN "\e[0;96m"
#define CFMT_COLOR_BLINK_WHITE "\e[0;97m"

#define CFMT_COLOR_RESET "\e[0m"
#define CFMT_COLOR_BOLD "\e[1m"

char *cfmt_tbprintf(const char *s, ...);
INT cfmt_logf(const INT level, char *s, ...);
#endif /* __CMFT_H__ */