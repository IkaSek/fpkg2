#ifndef __PKG_H__
#define __PKG_H__

#include "API.h"

typedef struct Pkg Pkg;

#include "API.h"

Pkg *Pkg_init(API_IAllocator ialloc);
void Pkg_set_name(Pkg *pkg, UCHAR *name);
UCHAR *Pkg_get_name(const Pkg *pkg);
void Pkg_set_version(Pkg *pkg, UCHAR *version);
UCHAR *Pkg_get_version(const Pkg *pkg);
void Pkg_set_description(Pkg *pkg, UCHAR *description);
UCHAR *Pkg_get_description(const Pkg *pkg);
void Pkg_set_depends(Pkg *pkg, API_ByteArray depends);
API_ByteArray Pkg_get_depends(const Pkg *pkg);
void Pkg_set_conflicts(Pkg *pkg, API_ByteArray conflicts);
API_ByteArray Pkg_get_conflicts(const Pkg *pkg);
void Pkg_set_optdepends(Pkg *pkg, API_ByteArray optdepends);
API_ByteArray Pkg_get_optdepends(const Pkg *pkg);
void Pkg_set_suggests(Pkg *pkg, API_ByteArray suggests);
API_ByteArray Pkg_get_suggests(const Pkg *pkg);
void Pkg_set_replaces(Pkg *pkg, API_ByteArray replaces);
API_ByteArray Pkg_get_replaces(const Pkg *pkg);
void Pkg_set_files(Pkg *pkg, API_ByteArray files);
API_ByteArray Pkg_get_files(const Pkg *pkg);
void Pkg_destroy(Pkg *pkg);

#endif /* __PKG_H__ */
