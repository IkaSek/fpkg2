#ifndef __REPO_H__
#define __REPO_H__
#include <API.h>

typedef struct Repo Repo;
UCHAR *Repo_get_url(const Repo *repo);

#endif