#include <emscripten/bind.h>
#include "utils.h"

using namespace emscripten;

std::string tostring(reg_t n, int base, int width, bool zero) {
  if (zero && (n == 0))
    return "0";

  std::string s = "";
  do {
    int bit = n % base;
    if (bit > 9)
      s.insert(0, 1, ('a' + bit - 10));
    else
      s.insert(0, 1, ('0' + bit));
    n = n / base;
  } while(n != 0);
  s = std::string(width - s.length(), '0') + s;
  return s;
}

EMSCRIPTEN_BINDINGS(csr_visual) {
  enum_<handle_t>("HANDLE")
    .value("CSR_HEX_CHANGE", CSR_HEX_CHANGE)
    .value("CSR_BIN_CHANGE", CSR_BIN_CHANGE)
    .value("CSR_FIELD_CHANGE", CSR_FIELD_CHANGE);
}