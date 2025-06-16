#include <API.h>
#include <stdint.h>

FPKG_API_PUBLIC uint64_t API_min(uint64_t a, uint64_t b) {
  return (a > b) ? b : a;
}
FPKG_API_PUBLIC uint64_t API_max(uint64_t a, uint64_t b) {
  return (a < b) ? b : a;
}
FPKG_API_PUBLIC uint64_t API_nearest_pow2(uint64_t a) {
  return a == 1 ? 1 : __builtin_clzl(a - 1);
}

FPKG_API_PUBLIC uint64_t API_get_version() { return FPKG_VERSION; }