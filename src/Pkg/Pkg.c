#include <API.h>
#include <Pkg.h>
#include <Repo.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

struct Pkg {
  UCHAR *author;
  UCHAR *name;
  UCHAR *version;
  UCHAR *description;
  const Repo *repo;

  API_ByteArray depends;
  API_ByteArray conflicts;
  API_ByteArray optdepends;
  API_ByteArray suggests;
  API_ByteArray replaces;
  API_ByteArray files;

  API_IAllocator alloc;
};

FPKG_API_PUBLIC Pkg *Pkg_init(API_IAllocator ialloc, const Repo *repo) {
  Pkg *pkg = ialloc.alloc(sizeof(Pkg), ialloc.ctx);
  memset(pkg, 0, sizeof(Pkg));
  pkg->alloc = ialloc;
  pkg->repo = repo;
  return pkg;
}

FPKG_API_PUBLIC const Repo *Pkg_get_repo(Pkg *pkg) { return pkg->repo; }

FPKG_API_PUBLIC void Pkg_set_name(Pkg *pkg, UCHAR *name) {
  pkg->name = API_ucstrdup(pkg->alloc, name);
};

FPKG_API_PUBLIC UCHAR *Pkg_get_name(const Pkg *pkg) { return pkg->name; }

FPKG_API_PUBLIC void Pkg_set_version(Pkg *pkg, UCHAR *version) {
  pkg->version = API_ucstrdup(pkg->alloc, version);
}

FPKG_API_PUBLIC UCHAR *Pkg_get_version(const Pkg *pkg) { return pkg->version; }

FPKG_API_PUBLIC void Pkg_set_description(Pkg *pkg, UCHAR *description) {
  pkg->description = API_ucstrdup(pkg->alloc, description);
}

FPKG_API_PUBLIC UCHAR *Pkg_get_description(const Pkg *pkg) {
  return pkg->description;
}

FPKG_API_PUBLIC void Pkg_set_depends(Pkg *pkg, API_ByteArray depends) {
  pkg->depends = API_ByteArray_dup(depends, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_depends(const Pkg *pkg) {
  return pkg->depends;
}

FPKG_API_PUBLIC void Pkg_set_conflicts(Pkg *pkg, API_ByteArray conflicts) {
  pkg->conflicts = API_ByteArray_dup(conflicts, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_conflicts(const Pkg *pkg) {
  return pkg->conflicts;
}

FPKG_API_PUBLIC void Pkg_set_optdepends(Pkg *pkg, API_ByteArray optdepends) {
  pkg->optdepends = API_ByteArray_dup(optdepends, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_optdepends(const Pkg *pkg) {
  return pkg->optdepends;
}

FPKG_API_PUBLIC void Pkg_set_suggests(Pkg *pkg, API_ByteArray suggests) {
  pkg->suggests = API_ByteArray_dup(suggests, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_suggests(const Pkg *pkg) {
  return pkg->suggests;
}

FPKG_API_PUBLIC void Pkg_set_replaces(Pkg *pkg, API_ByteArray replaces) {
  pkg->replaces = API_ByteArray_dup(replaces, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_replaces(const Pkg *pkg) {
  return pkg->replaces;
}

FPKG_API_PUBLIC void Pkg_set_files(Pkg *pkg, API_ByteArray files) {
  pkg->files = API_ByteArray_dup(files, pkg->alloc);
}

FPKG_API_PUBLIC API_ByteArray Pkg_get_files(const Pkg *pkg) {
  return pkg->files;
}

FPKG_API_PUBLIC void Pkg_destroy(Pkg *pkg) {
  if (pkg->alloc.free != NULL) {
#define FREE_(W)                                                               \
  do {                                                                         \
    pkg->alloc.free(W, pkg->alloc.ctx);                                        \
  } while (0);
    FREE_(pkg->name);
    FREE_(pkg->description);
    FREE_(pkg->author);
    FREE_(pkg->version);
    FREE_(pkg->depends.buf);
    FREE_(pkg->conflicts.buf);
    FREE_(pkg->optdepends.buf);
    FREE_(pkg->replaces.buf);
    FREE_(pkg->files.buf);
    FREE_(pkg->suggests.buf);
    FREE_(pkg);
#undef FREE_
  }
}