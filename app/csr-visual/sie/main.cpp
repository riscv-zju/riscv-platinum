#include <emscripten/bind.h>
#include <algorithm>
#include "utils.h"

using namespace emscripten;

struct csr_sie_str_t {
  std::string rev0;
  std::string seip;
  std::string rev1;
  std::string stip;
  std::string rev2;
  std::string ssip;
  std::string rev3;
  std::string hex;
  std::string bin;
};

struct csr_sie_t {
  unsigned long long rev0;
  unsigned char seip;
  unsigned char rev1;
  unsigned char stip;
  unsigned char rev2;
  unsigned char ssip;
  unsigned char rev3;
};

reg_t field_to_reg (csr_sie_str_t& in) {
  // format field
  in.rev0 = "0";
  in.rev1 = "0";
  in.rev2 = "0";
  in.rev3 = "0";
  in.seip = in.seip.substr(0, std::min(1UL, in.seip.length()));
  in.stip = in.stip.substr(0, std::min(1UL, in.stip.length()));
  in.ssip = in.ssip.substr(0, std::min(1UL, in.ssip.length()));

  csr_sie_t fields;
  fields.rev0 = std::stol(in.rev0, 0, 2);
  fields.seip = std::stol(in.seip, 0, 2);
  fields.rev1 = std::stol(in.rev1, 0, 2);
  fields.stip = std::stol(in.stip, 0, 2);
  fields.rev2 = std::stol(in.rev2, 0, 2);
  fields.ssip = std::stol(in.ssip, 0, 2);
  fields.rev3 = std::stol(in.rev3, 0, 2);

  reg_t reg = 0ULL
    | TRUNC(fields.rev0, 54) << 10
    | TRUNC(fields.seip, 1) << 9
    | TRUNC(fields.rev1, 3) << 6
    | TRUNC(fields.stip, 1) << 5
    | TRUNC(fields.rev2, 3) << 2
    | TRUNC(fields.ssip, 1) << 1
    | TRUNC(fields.rev3, 1);

  return reg;
}

void reg_to_field (reg_t reg, csr_sie_str_t& in) {
  csr_sie_t fields;
  fields.rev0 = TRUNC(reg >> 10, 54);
  fields.seip = TRUNC(reg >> 9, 1);
  fields.rev1 = TRUNC(reg >> 6, 3);
  fields.stip = TRUNC(reg >> 5, 1);
  fields.rev2 = TRUNC(reg >> 2, 3);
  fields.ssip = TRUNC(reg >> 1, 1);
  fields.rev3 = TRUNC(reg >> 0, 1);

  in.rev0 = tostring(fields.rev0, 2, 54, true);
  in.seip = tostring(fields.seip, 2, 1);
  in.rev1 = tostring(fields.rev1, 2, 3, true);
  in.stip = tostring(fields.stip, 2, 1);
  in.rev2 = tostring(fields.rev2, 2, 3, true);
  in.ssip = tostring(fields.ssip, 2, 1);
  in.rev3 = tostring(fields.rev3, 2, 1, true);
}

csr_sie_str_t sie_handler(csr_sie_str_t csr, handle_t h) {
  if (h == CSR_FIELD_CHANGE) {
    reg_t reg = field_to_reg(csr);
    csr.bin = tostring(reg, 2, 64);
    csr.hex = tostring(reg, 16, 16);
  } else {
    reg_t reg = 0;
    if (h == CSR_BIN_CHANGE) {
      csr.bin = csr.bin.substr(0, std::min(64UL, csr.bin.length()));
      reg = std::stoull(csr.bin, 0, 2);
        printf("Here\n");
      csr.hex = tostring(reg, 16, 16);
    } else /* CSR_HEX_CHANGE */ {
      csr.hex = csr.hex.substr(0, std::min(16UL, csr.hex.length()));
      reg = std::stoull(csr.hex, 0, 16);
      csr.bin = tostring(reg, 2, 64);
    }
    reg_to_field(reg, csr);
  }
  return csr;
}

EMSCRIPTEN_BINDINGS(sie_visual) {
  value_object<csr_sie_str_t>("csr_sie_t")
  .field("rev0", &csr_sie_str_t::rev0)
  .field("seip", &csr_sie_str_t::seip)
  .field("rev1", &csr_sie_str_t::rev1)
  .field("stip", &csr_sie_str_t::stip)
  .field("rev2", &csr_sie_str_t::rev2)
  .field("ssip", &csr_sie_str_t::ssip)
  .field("rev3", &csr_sie_str_t::rev3)
  .field("hex", &csr_sie_str_t::hex)
  .field("bin", &csr_sie_str_t::bin);

  function("sie_handler", &sie_handler);
}