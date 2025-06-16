#include "BDATA.h"
#include <API.h>
#include <Pkg.h>
#include <Repo.h>
#include <string.h>

struct Repo {
  UCHAR *url;
  UCHAR *name;
  API_ByteArray pkgs;
  API_Arena arena;
  API_IAllocator iarena;
};

FPKG_API_PUBLIC Repo *Repo_init() {
  Repo *r = malloc(sizeof(Repo));
  memset(r, 0, sizeof(Repo));
  r->iarena = (API_IAllocator){.alloc = (API_IAllocator_Alloc)API_Arena_alloc,
                               .free = NULL,
                               .ctx = &r->arena};
}

FPKG_API_PRIVATE void __Repo_bdata_pkgs(UCHAR *uc, Repo *r, UINT pkgs_len) {
  for (UINT i = 0; i < pkgs_len; ++i) {
    UINT bytecode = *(UINT *)uc;
    uc += sizeof(UINT);

    Pkg *p;

    p = Pkg_init();

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