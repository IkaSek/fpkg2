#include "Plugs/plg.h"
#include <API.h>
#include <API_plugsapi.h>
#include <FS.h>
#include <Pkg.h>
#include <Repo.h>
#include <cfmt.h>
#include <linux/limits.h>
#include <string.h>

struct __fetch_url_file_pair {
  const char *url;
  FILE *fil;
} __attribute__((packed));

FPKG_API_PUBLIC INT Pkg_fetch_mul(API_ByteArray ps) {
  API_Arena a = {0};
  API_IAllocator alloc = {(API_IAllocator_Alloc)API_Arena_alloc, NULL, &a};
  API_ByteArray fetch_vc = {0};
  INT retc;

  char tmpbuf[PATH_MAX];
  FS_gettempd(tmpbuf, PATH_MAX, 6);
  FS_mkdirr(tmpbuf, 0700);

  cfmt_logf(CFMT_LOG_LEVEL_LOG, "Starting to fetch for %zu pkgs,", ps.blen);

  for (size_t i = 0; i < ps.blen; ++i) {
    printf("\t%s", Pkg_get_name(ps.buf[i]));
    const Repo *parent_repo = Pkg_get_repo(ps.buf[i]);
    UCHAR *url = Repo_get_url(parent_repo);

    char *archive_url = API_cslib_strdup(
        alloc, cfmt_tbprintf("%s/%s-%s.pkg", ucstocs(url),
                             ucstocs(Pkg_get_name(ps.buf[i])),
                             ucstocs(Pkg_get_version(ps.buf[i]))));
    char *archive_file = API_cslib_strdup(
        alloc, cfmt_tbprintf("%s/%s-%s.pkg", ucstocs(tmpbuf),
                             ucstocs(Pkg_get_name(ps.buf[i])),
                             ucstocs(Pkg_get_version(ps.buf[i]))));

    FILE *fil = fopen(archive_file, "wb");
    struct __fetch_url_file_pair pp = {
        .fil = fil,
        .url = archive_url,
    };
    API_ByteArray_push(&fetch_vc, &pp);
  }
  fpkg_api_plug_find_actors(
      PLUG_ACTOR_DOWNLOADER,
      PLACEHOLDER_ERR FPKG_API_ERROR("...at verbose") true, true, fetch_vc.blen,
      fetch_vc.buf, &retc);
#define _CLEANUP                                                               \
  for (size_t i = 0; i < fetch_vc.blen; ++i) {                                 \
    struct __fetch_url_file_pair pp =                                          \
        *(struct __fetch_url_file_pair *)(fetch_vc.buf[i]);                    \
    fclose(pp.fil);                                                            \
  }
  if (retc != 0) {
    cfmt_logf(CFMT_LOG_LEVEL_WRN,
              "Downloader actor errored out. Other actions might be hindered.");
    _CLEANUP;
    return -1;
  }

  _CLEANUP;
#undef _CLEANUP
}