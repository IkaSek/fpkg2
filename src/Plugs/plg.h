#ifndef __PLG_H__
#define __PLG_H__

#include <API.h>
#include <stdio.h>

#define PLUG_ACTOR_OPT_EXCLUDEOTHERS 0x00010000
#define PLUG_ACTOR_DOWNLOADER 0x00000001
#define PLUG_ACTOR_DECOMPRESSOR 0x00000002
#define PLUG_ACTOR_HOOKHANDLER 0x00000003

#define PLUG_CONSTRUCTOR __attribute__((constructor))
#define PLUG_DESTRUCTOR __attribute__((destructor))

typedef FN_PTR(int, fpkg_plugs_act_t)(size_t, void *);
typedef FN_PTR(void, fpkg_plugs_debug_t)();

typedef struct Plugin Plugin;
struct Plugin {
  const char *name;
  const char *version;

  INT actor;
  fpkg_plugs_act_t act;
  fpkg_plugs_debug_t debug;
  INT opts;
};
typedef FN_PTR(Plugin *, fpkg_plugs_get_hndl_t)();

#define PLUG_HEADER(NAME, VERSION, ACTOR, ACT, OPTS)                           \
  bool plug_debug = false;                                                     \
  void debug() { plug_debug = true; }                                          \
                                                                               \
  Plugin plugin = {.name = NAME,                                               \
                   .version = VERSION,                                         \
                   .actor = ACTOR,                                             \
                   .act = ACT,                                                 \
                   .debug = debug,                                             \
                   .opts = OPTS};                                              \
                                                                               \
  Plugin *fpkg_plug_get_hndl() { return &plugin; }

#endif