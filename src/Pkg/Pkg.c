#include "../Pkg.h"
#include "../API.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

struct Pkg {
  UCHAR *author;
  UCHAR *name;
  UCHAR *version;
  UCHAR *description;

  API_ByteArray *depends;
  API_ByteArray *conflicts;
  API_ByteArray *optdepends;
  API_ByteArray *suggests;
  API_ByteArray *replaces;
  API_ByteArray *files;
};

FPKG_API_PUBLIC Pkg *Pkg_init() {
  Pkg *pkg = malloc(sizeof(Pkg));
  memset(pkg, 0, sizeof(Pkg));
  return pkg;
}

FPKG_API_PUBLIC void Pkg_set_name(Pkg *pkg, UCHAR *name) {
  pkg->name = API_ucstrdup(libc_alloc, name);
};

FPKG_API_PUBLIC UCHAR *Pkg_get_name(Pkg *pkg) { return pkg->name; }

FPKG_API_PUBLIC void Pkg_set_version(Pkg *pkg, UCHAR *version) {
  pkg->version = API_ucstrdup(libc_alloc, version);
}

FPKG_API_PUBLIC UCHAR *Pkg_get_version(Pkg *pkg) { return pkg->version; }

FPKG_API_PUBLIC void Pkg_set_description(Pkg *pkg, UCHAR *description) {
  ;
  pkg->description = API_ucstrdup(libc_alloc, description);
}

FPKG_API_PUBLIC UCHAR *Pkg_get_description(Pkg *pkg) {
  return pkg->description;
}

FPKG_API_PUBLIC void Pkg_set_depends(Pkg *pkg, API_ByteArray *depends) {
  pkg->depends = depends;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_depends(Pkg *pkg) {
  return pkg->depends;
}

FPKG_API_PUBLIC void Pkg_set_conflicts(Pkg *pkg, API_ByteArray *conflicts) {
  pkg->conflicts = conflicts;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_conflicts(Pkg *pkg) {
  return pkg->conflicts;
}

FPKG_API_PUBLIC void Pkg_set_optdepends(Pkg *pkg, API_ByteArray *optdepends) {
  pkg->optdepends = optdepends;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_optdepends(Pkg *pkg) {
  return pkg->optdepends;
}

FPKG_API_PUBLIC void Pkg_set_suggests(Pkg *pkg, API_ByteArray *suggests) {
  pkg->suggests = suggests;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_suggests(Pkg *pkg) {
  return pkg->suggests;
}

FPKG_API_PUBLIC void Pkg_set_replaces(Pkg *pkg, API_ByteArray *replaces) {
  pkg->replaces = replaces;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_replaces(Pkg *pkg) {
  return pkg->replaces;
}

FPKG_API_PUBLIC void Pkg_set_files(Pkg *pkg, API_ByteArray *files) {
  pkg->files = files;
}

FPKG_API_PUBLIC API_ByteArray *Pkg_get_files(Pkg *pkg) { return pkg->files; }

FPKG_API_PUBLIC void Pkg_destroy(Pkg *pkg) {
  free(pkg->name);
  free(pkg->description);
  free(pkg->version);
  free(pkg);
}