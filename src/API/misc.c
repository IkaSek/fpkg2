#include <API.h>
#include <stdint.h>

FPKG_API_PUBLIC UINT API_min(UINT a, UINT b) { return (a > b) ? b : a; }
FPKG_API_PUBLIC UINT API_max(UINT a, UINT b) { return (a < b) ? b : a; }
FPKG_API_PUBLIC UINT API_nearest_pow2(UINT a) {
  return a == 1 ? 1 : __builtin_clzl(a - 1);
}
FPKG_API_PUBLIC UINT API_floor(FLOAT64 a) { return (UINT)a; }
FPKG_API_PUBLIC UINT API_ceil(FLOAT64 a) { return (UINT)a + 1; }

FPKG_API_PUBLIC UINT API_get_version() { return FPKG_VERSION; }