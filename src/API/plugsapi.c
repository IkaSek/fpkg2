#include "../Plugs/plg.h"
#include <API.h>
#include <API_Errors.sp.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

FPKG_API_PRIVATE API_ByteArray plugs = {0};

FPKG_API_PUBLIC Plugin *fpkg_api_plug_get_hndl(const char *plugfile) {
  void *dl = dlopen(plugfile, RTLD_NOW | RTLD_GLOBAL);
  if (!dl) {
    return NULL;
  }
  dlerror();
  fpkg_plugs_get_hndl_t get_hndl = dlsym(dl, "fpkg_plug_get_hndl");
  if (!get_hndl) {
    return NULL;
  }
  dlerror();

  Plugin *hndl = get_hndl();
  return hndl;
}
FPKG_API_PUBLIC int fpkg_api_plug_register(Plugin *plugin, bool verbose) {
  if (verbose) {
    printf("\t...loading plug: %s-%s\n", plugin->name, plugin->version);
  }
  API_ByteArray_push(&plugs, plugin);
  return 0;
}

FPKG_API_PUBLIC INT fpkg_api_plug_find_actors(UINT type, bool verbose,
                                              bool single_instance,
                                              size_t data_size, void *data,
                                              INT *retc) {
  if (verbose) {
    printf("\t...searching for plug actors of type %llu\n", type);
  }
  for (size_t i = 0; i < plugs.blen; ++i) {
    Plugin *plugin = (Plugin *)plugs.buf[i];
    if (plugin->actor == type) {
      INT act_ret = plugin->act(data_size, data);
      if (act_ret && retc != NULL) {
        (*retc)++;
      }

      if (single_instance) {
        if (act_ret != 0) {
          return API_ERROR_PLUGERROR;
        }
        return 0;
      }
    }
  }

  if (retc != NULL && *retc != 0) {
    return API_ERROR_PLUGERROR;
  }
  return 0;
}

FPKG_API_PUBLIC void fpkg_api_plug_deregister_all(bool verbose) {
  API_ByteArray_free(&plugs);
}