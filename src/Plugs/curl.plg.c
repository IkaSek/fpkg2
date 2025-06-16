#include <curl/curl.h>
#include <curl/multi.h>

#include "plg.h"

#ifndef PLUG_CONFIG_HANDLES_N
#define PLUG_CONFIG_HANDLES_N 10
#endif

CURL *curl_handles[PLUG_CONFIG_HANDLES_N];
CURLM *curlm_handle;

int act(size_t len, void *VP_url_file);
PLUG_HEADER("curl", "0.0.1", PLUG_ACTOR_DOWNLOADER, act,
            PLUG_ACTOR_OPT_EXCLUDEOTHERS)

PLUG_CONSTRUCTOR void init() {
  for (size_t i = 0; i < PLUG_CONFIG_HANDLES_N; ++i) {
    curl_handles[i] = curl_easy_init();
    curl_multi_add_handle(curlm_handle, curl_handles[i]);
  }
  curlm_handle = curl_multi_init();
}

struct url_file {
  const char *url;
  const FILE *file;
};

size_t act_write(char *data, size_t s, size_t nmemb, void *userdata) {
  if (plug_debug) {
    printf("\t...CURL: Written %zu bytes\n", s * nmemb);
  }

  return fwrite(data, s, nmemb, (FILE *)userdata);
}

int act(size_t len, void *VP_url_file) {
  int hndls;
  int curlwait;
  for (size_t pp = 0; pp < len;) {
    for (size_t i = 0; i < PLUG_CONFIG_HANDLES_N; ++i) {
      struct url_file uf = *(struct url_file *)VP_url_file;
      curl_easy_setopt(curl_handles[i % PLUG_CONFIG_HANDLES_N], CURLOPT_URL,
                       uf.url);
      curl_easy_setopt(curl_handles[i % PLUG_CONFIG_HANDLES_N],
                       CURLOPT_WRITEFUNCTION, act_write);
      curl_easy_setopt(curl_handles[i % PLUG_CONFIG_HANDLES_N],
                       CURLOPT_WRITEDATA, uf.file);

      if (hndls % PLUG_CONFIG_HANDLES_N == 0) {
        curl_multi_wait(curlm_handle, NULL, 0, 50, &curlwait);
      }
    }
    curl_multi_perform(curlm_handle, &hndls);
    pp += PLUG_CONFIG_HANDLES_N;
  }
  return curlwait;
}

PLUG_DESTRUCTOR void destroy() {
  for (size_t i = 0; i < PLUG_CONFIG_HANDLES_N; ++i)
    curl_easy_cleanup(curl_handles[i]);
  curl_multi_cleanup(curlm_handle);
}
