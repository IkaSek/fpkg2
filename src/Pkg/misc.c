#include <API.h>
#include <Pkg.h>

FPKG_API_PUBLIC bool Pkg_cmpver(Pkg *p1, Pkg *p2) {
  return API_ucstrcmp(Pkg_get_version(p1), Pkg_get_version(p2));
}