#include <emscripten/bind.h>
#include <algorithm>
#include "utils.h"

using namespace emscripten;

struct csr_mie_str_t {
  std::string rev0;
  std::string meip;
  std::string rev1;
  std::string seip;
  std::string rev2;
  std::string mtip;
  std::string rev3;
  std::string stip;
  std::string rev4;
  std::string msip;
  std::string rev5;
  std::string ssip;
  std::string rev6;
  std::string hex;
  std::string bin;
};

struct csr_mie_t {
  unsigned long long rev0;
  unsigned char meip;
  unsigned char rev1;
  unsigned char seip;
  unsigned char rev2;
  unsigned char mtip;
  unsigned char rev3;
  unsigned char stip;
  unsigned char rev4;
  unsigned char msip;
  unsigned char rev5;
  unsigned char ssip;
  unsigned char rev6;
};

reg_t field_to_reg (csr_mie_str_t& in) {
  // format field
  in.rev0 = "0";
  in.rev1 = "0";
  in.rev2 = "0";
  in.rev3 = "0";
  in.rev4 = "0";
  in.rev5 = "0";
  in.rev6 = "0";
  in.meip = in.meip.substr(0, std::min(1UL, in.meip.length()));
  in.seip = in.seip.substr(0, std::min(1UL, in.seip.length()));
  in.mtip = in.mtip.substr(0, std::min(1UL, in.mtip.length()));
  in.stip = in.stip.substr(0, std::min(1UL, in.stip.length()));
  in.msip = in.msip.substr(0, std::min(1UL, in.msip.length()));
  in.ssip = in.ssip.substr(0, std::min(1UL, in.ssip.length()));

  csr_mie_t fields;
  fields.rev0 = std::stol(in.rev0, 0, 2);
  fields.meip = std::stol(in.meip, 0, 2);
  fields.rev1 = std::stol(in.rev1, 0, 2);
  fields.seip = std::stol(in.seip, 0, 2);
  fields.rev2 = std::stol(in.rev2, 0, 2);
  fields.mtip = std::stol(in.mtip, 0, 2);
  fields.rev3 = std::stol(in.rev3, 0, 2);
  fields.stip = std::stol(in.stip, 0, 2);
  fields.rev4 = std::stol(in.rev4, 0, 2);
  fields.msip = std::stol(in.msip, 0, 2);
  fields.rev5 = std::stol(in.rev5, 0, 2);
  fields.ssip = std::stol(in.ssip, 0, 2);
  fields.rev6 = std::stol(in.rev6, 0, 2);

  reg_t reg = 0ULL
    | TRUNC(fields.rev0, 52) << 12
    | TRUNC(fields.meip, 1) << 11
    | TRUNC(fields.rev1, 1) << 10
    | TRUNC(fields.seip, 1) << 9
    | TRUNC(fields.rev2, 1) << 8
    | TRUNC(fields.mtip, 1) << 7
    | TRUNC(fields.rev3, 1) << 6
    | TRUNC(fields.stip, 1) << 5
    | TRUNC(fields.rev4, 1) << 4
    | TRUNC(fields.msip, 1) << 3
    | TRUNC(fields.rev5, 1) << 2
    | TRUNC(fields.ssip, 1) << 1
    | TRUNC(fields.rev6, 1);

  return reg;
}

void reg_to_field (reg_t reg, csr_mie_str_t& in) {
  csr_mie_t fields;

  fields.rev0 = TRUNC(reg >> 12, 52);
  fields.meip = TRUNC(reg >> 11, 1);
  fields.rev1 = TRUNC(reg >> 10, 1);
  fields.seip = TRUNC(reg >> 9, 1);
  fields.rev2 = TRUNC(reg >> 8, 1);
  fields.mtip = TRUNC(reg >> 7, 1);
  fields.rev3 = TRUNC(reg >> 6, 1);
  fields.stip = TRUNC(reg >> 5, 1);
  fields.rev4 = TRUNC(reg >> 4, 1);
  fields.msip = TRUNC(reg >> 3, 1);
  fields.rev5 = TRUNC(reg >> 2, 1);
  fields.ssip = TRUNC(reg >> 1, 1);
  fields.rev6 = TRUNC(reg >> 0, 1);

  in.rev0 = tostring(fields.rev0, 2, 52, true);
  in.meip = tostring(fields.meip, 2, 1);
  in.rev1 = tostring(fields.rev1, 2, 1, true);
  in.seip = tostring(fields.seip, 2, 1);
  in.rev2 = tostring(fields.rev2, 2, 1, true);
  in.mtip = tostring(fields.mtip, 2, 1);
  in.rev3 = tostring(fields.rev3, 2, 1, true);
  in.stip = tostring(fields.stip, 2, 1);
  in.rev4 = tostring(fields.rev4, 2, 1, true);
  in.msip = tostring(fields.msip, 2, 1);
  in.rev5 = tostring(fields.rev5, 2, 1, true);
  in.ssip = tostring(fields.ssip, 2, 1);
  in.rev6 = tostring(fields.rev6, 2, 1, true);
}

csr_mie_str_t mie_handler(csr_mie_str_t csr, handle_t h) {
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

EMSCRIPTEN_BINDINGS(mie_visual) {
  value_object<csr_mie_str_t>("csr_mie_t")
  .field("rev0", &csr_mie_str_t::rev0)
  .field("meip", &csr_mie_str_t::meip)
  .field("rev1", &csr_mie_str_t::rev1)
  .field("seip", &csr_mie_str_t::seip)
  .field("rev2", &csr_mie_str_t::rev2)
  .field("mtip", &csr_mie_str_t::mtip)
  .field("rev3", &csr_mie_str_t::rev3)
  .field("stip", &csr_mie_str_t::stip)
  .field("rev4", &csr_mie_str_t::rev4)
  .field("msip", &csr_mie_str_t::msip)
  .field("rev5", &csr_mie_str_t::rev5)
  .field("ssip", &csr_mie_str_t::ssip)
  .field("rev6", &csr_mie_str_t::rev6)
  .field("hex", &csr_mie_str_t::hex)
  .field("bin", &csr_mie_str_t::bin);

  function("mie_handler", &mie_handler);
}