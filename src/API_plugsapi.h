#ifndef __API_PLUGSAPI_H__
#define __API_PLUGSAPI_H__
#include "Plugs/plg.h"
#include <API.h>

FPKG_API_PUBLIC Plugin *fpkg_api_plug_get_hndl(const char *plugfile);
FPKG_API_PUBLIC int fpkg_api_plug_register(Plugin *plugin, bool verbose);
FPKG_API_PUBLIC INT fpkg_api_plug_find_actors(UINT type, bool verbose,
                                              bool single_instance,
                                              size_t data_size, void *data,
                                              INT *retc);

#endif