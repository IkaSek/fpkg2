#include "BDATA.h"
#include <API.h>
#include <Pkg.h>
#include <Repo.h>
#include <stdlib.h>
#include <string.h>

struct Repo {
  UCHAR *url;
  UCHAR *name;
  API_ByteArray pkgs;
  API_Arena arena;
  API_IAllocator iarena;
};

FPKG_API_INLN void __Repo_bdata_pop_mem(UCHAR **uc, size_t niter,
                                        API_ByteArray *ba) {
  *uc += sizeof(size_t);
  for (size_t i = 0; i < niter; ++i) {
    API_ByteArray_push(ba, uc);
    *uc += API_ucnstrlen(*uc);
  }
}

#define ELSEIF_BA_BRANCH(WHAT, THEN)                                           \
  else if (bytecode == WHAT) {                                                 \
    API_ByteArray buf = {0};                                                   \
    __Repo_bdata_pop_mem(&uc, *(size_t *)uc, &buf);                            \
    uc += sizeof(size_t);                                                      \
    THEN(p, buf);                                                              \
    API_ByteArray_free(&buf);                                                  \
  }

FPKG_API_PRIVATE void __Repo_bdata_pkgs(UCHAR *uc, Repo *r, UINT pkgs_len) {
  for (UINT i = 0; i < pkgs_len; ++i) {
    UINT bytecode = *(UINT *)uc;
    uc += sizeof(UINT);

    Pkg *p = Pkg_init(r->iarena, r);
    API_ByteArray_push(&r->pkgs, p);

    if (bytecode == __REPO_BDATA_REPO_PKG_AUTHOR) {
      continue;
    } else if (bytecode == REPO_BDATA_REPO_PKG_NAM) {
      UCHAR *nam = uc;
      Pkg_set_name(p, API_ucstrdup(r->iarena, nam));
      uc += API_ucnstrlen(nam);
    } else if (bytecode == REPO_BDATA_REPO_PKG_DESC) {
      UCHAR *desc = uc;
      Pkg_set_description(p, API_ucstrdup(r->iarena, desc));
      uc += API_ucnstrlen(desc);
    }
    ELSEIF_BA_BRANCH(REPO_BDATA_REPO_PKG_DEPENDS, Pkg_set_depends)
    ELSEIF_BA_BRANCH(REPO_BDATA_REPO_PKG_CONFLICTS, Pkg_set_conflicts)
    ELSEIF_BA_BRANCH(REPO_BDATA_REPO_PKG_OPTDEPS, Pkg_set_optdepends)
    ELSEIF_BA_BRANCH(REPO_BDATA_REPO_PKG_SUGGESTS, Pkg_set_suggests)
    ELSEIF_BA_BRANCH(REPO_BDATA_REPO_PKG_FILES, Pkg_set_files)
  }
}

FPKG_API_PRIVATE void __Repo_bdata(UCHAR *uc, Repo *r) {
  for (size_t i = 0; i < API_ucstrlen(uc); ++i) {
    UINT bytecode = *(UINT *)uc;
    uc += sizeof(UINT);
    if (bytecode == REPO_BDATA_REPO_NAME) {
      r->name = API_ucstrdup(r->iarena, uc);
      uc += API_ucnstrlen(r->name);
    } else if (bytecode == REPO_BDATA_REPO_URL) {
      r->url = API_ucstrdup(r->iarena, uc);
      uc += API_ucnstrlen(r->url);
    } else if (bytecode == REPO_BDATA_REPO_PKGS_LEN) {
      UINT pkgs_len = *(UINT *)uc;
      uc += sizeof(UINT);
      __Repo_bdata_pkgs(uc, r, pkgs_len);
    }
  }
}

FPKG_API_PUBLIC Repo *Repo_init(UCHAR *stream) {
  Repo *r = malloc(sizeof(Repo));
  memset(r, 0, sizeof(Repo));
  r->iarena = (API_IAllocator){.alloc = (API_IAllocator_Alloc)API_Arena_alloc,
                               .free = NULL,
                               .ctx = &r->arena};
  __Repo_bdata(stream, r);

  API_ByteArray_sort(&r->pkgs);

  return r;
}

FPKG_API_PRIVATE int cmppkgs(const void *a, const void *b) {
  const Pkg *p1 = a;
  const Pkg *p2 = b;

  return !API_ucstrcmp(Pkg_get_name(p1), Pkg_get_name(p2)) &&
                 (Pkg_get_version(p1) == NULL || Pkg_get_version(p2) == NULL)
             ? 1
             : !API_ucstrcmp(Pkg_get_version(p1), Pkg_get_version(p2));
}

FPKG_API_PUBLIC Pkg *Repo_find_pkg(Repo *repo, Pkg *template) {
  return *(Pkg **)bsearch(template, repo->pkgs.buf, repo->pkgs.blen,
                          sizeof(Pkg *), cmppkgs);
}

FPKG_API_PUBLIC UCHAR *Repo_get_url(const Repo *repo) { return repo->url; }
