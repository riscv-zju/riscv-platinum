#include <emscripten/bind.h>
#include <algorithm>
#include "utils.h"

using namespace emscripten;

struct csr_sstatus_str_t {
  std::string sd;
  std::string rev0;
  std::string uxl;
  std::string rev1;
  std::string mxr;
  std::string sum;
  std::string rev2;
  std::string xs;
  std::string fs;
  std::string rev3;
  std::string vs;
  std::string spp;
  std::string rev4;
  std::string ube;
  std::string spie;
  std::string rev5;
  std::string sie;
  std::string rev6;
  std::string hex;
  std::string bin;
};

struct csr_sstatus_t {
  unsigned char sd;
  unsigned long rev0;
  unsigned char uxl;
  unsigned short rev1;
  unsigned char mxr;
  unsigned char sum;
  unsigned char rev2;
  unsigned char xs;
  unsigned char fs;
  unsigned char rev3;
  unsigned char vs;
  unsigned char spp;
  unsigned char rev4;
  unsigned char ube;
  unsigned char spie;
  unsigned char rev5;
  unsigned char sie;
  unsigned char rev6;
};

reg_t field_to_reg (csr_sstatus_str_t& in) {
  // format field
  in.rev0 = "0";
  in.rev1 = "0";
  in.rev2 = "0";
  in.rev3 = "0";
  in.rev4 = "0";
  in.rev5 = "0";
  in.rev6 = "0";
  in.sd = in.sd.substr(0, std::min(1UL, in.sd.length()));
  in.uxl = in.uxl.substr(0, std::min(2UL, in.uxl.length()));
  in.mxr = in.mxr.substr(0, std::min(1UL, in.mxr.length()));
  in.sum = in.sum.substr(0, std::min(1UL, in.sum.length()));
  in.xs = in.xs.substr(0, std::min(2UL, in.xs.length()));
  in.fs = in.fs.substr(0, std::min(2UL, in.fs.length()));
  in.vs = in.vs.substr(0, std::min(2UL, in.vs.length()));
  in.spp = in.spp.substr(0, std::min(1UL, in.spp.length()));
  in.ube = in.ube.substr(0, std::min(1UL, in.ube.length()));
  in.spie = in.spie.substr(0, std::min(1UL, in.spie.length()));
  in.sie = in.sie.substr(0, std::min(1UL, in.sie.length()));

  csr_sstatus_t fields;
  fields.sd = std::stol(in.sd, 0, 2);
  fields.rev0 = std::stol(in.rev0, 0, 2);
  fields.uxl = std::stol(in.uxl, 0, 2);
  fields.rev1 = std::stol(in.rev1, 0, 2);
  fields.mxr = std::stol(in.mxr, 0, 2);
  fields.sum = std::stol(in.sum, 0, 2);
  fields.rev2 = std::stol(in.rev2, 0, 2);
  fields.xs = std::stol(in.xs, 0, 2);
  fields.fs = std::stol(in.fs, 0, 2);
  fields.rev3 = std::stol(in.rev3, 0, 2);
  fields.vs = std::stol(in.vs, 0, 2);
  fields.spp = std::stol(in.spp, 0, 2);
  fields.rev4 = std::stol(in.rev4, 0, 2);
  fields.ube = std::stol(in.ube, 0, 2);
  fields.spie = std::stol(in.spie, 0, 2);
  fields.rev5 = std::stol(in.rev5, 0, 2);
  fields.sie = std::stol(in.sie, 0, 2);
  fields.rev6 = std::stol(in.rev6, 0, 2);

  reg_t reg = 0ULL
    | TRUNC(fields.sd, 1) << 63
    | TRUNC(fields.rev0, 29) << 34
    | TRUNC(fields.uxl, 2) << 32 
    | TRUNC(fields.rev1, 12) << 20 
    | TRUNC(fields.mxr, 1) << 19 
    | TRUNC(fields.sum, 1) << 18 
    | TRUNC(fields.rev2, 1) << 17 
    | TRUNC(fields.xs, 2) << 15 
    | TRUNC(fields.fs, 2) << 13 
    | TRUNC(fields.rev3, 2) << 11 
    | TRUNC(fields.vs, 2) << 9 
    | TRUNC(fields.spp, 1) << 8 
    | TRUNC(fields.rev4, 1) << 7 
    | TRUNC(fields.ube, 1) << 6 
    | TRUNC(fields.spie, 1) << 5 
    | TRUNC(fields.rev5, 3) << 2 
    | TRUNC(fields.sie, 1) << 1
    | TRUNC(fields.rev6, 1);

  return reg;
}

void reg_to_field (reg_t reg, csr_sstatus_str_t& in) {
  csr_sstatus_t fields;
  fields.sd = TRUNC(reg >> 63, 1);
  fields.rev0 = TRUNC(reg >> 34, 29);
  fields.uxl = TRUNC(reg >> 32, 2);
  fields.rev1 = TRUNC(reg >> 20, 12);
  fields.mxr = TRUNC(reg >> 19, 1);
  fields.sum = TRUNC(reg >> 18, 1);
  fields.rev2 = TRUNC(reg >> 17, 1);
  fields.xs = TRUNC(reg >> 15, 2);
  fields.fs = TRUNC(reg >> 13, 2);
  fields.rev3 = TRUNC(reg >> 11, 2);
  fields.vs = TRUNC(reg >> 9, 2);
  fields.spp = TRUNC(reg >> 8, 1);
  fields.rev4 = TRUNC(reg >> 7, 1);
  fields.ube = TRUNC(reg >> 6, 1);
  fields.spie = TRUNC(reg >> 5, 1);
  fields.rev5 = TRUNC(reg >> 2, 3);
  fields.sie = TRUNC(reg >> 1, 1);
  fields.rev6 = TRUNC(reg >> 0, 1);

  in.sd = tostring(fields.sd, 2, 1);
  in.rev0 = tostring(fields.rev0, 2, 29, true);
  in.uxl = tostring(fields.uxl, 2, 2);
  in.rev1 = tostring(fields.rev1, 2, 12, true);
  in.mxr = tostring(fields.mxr, 2, 1);
  in.sum = tostring(fields.sum, 2, 1);
  in.rev2 = tostring(fields.rev2, 2, 1);
  in.xs = tostring(fields.xs, 2, 2);
  in.fs = tostring(fields.fs, 2, 2);
  in.rev3 = tostring(fields.rev3, 2, 2);
  in.vs = tostring(fields.vs, 2, 2);
  in.spp = tostring(fields.spp, 2, 1);
  in.rev4 = tostring(fields.rev4, 2, 1);
  in.ube = tostring(fields.ube, 2, 1);
  in.spie = tostring(fields.spie, 2, 1);
  in.rev5 = tostring(fields.rev5, 2, 3, true);
  in.sie = tostring(fields.sie, 2, 1);
  in.rev6 = tostring(fields.rev6, 2, 1, true);
}

csr_sstatus_str_t sstatus_handler(csr_sstatus_str_t csr, handle_t h) {
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

EMSCRIPTEN_BINDINGS(sstatus_visual) {
  // enum_<handle_t>("HANDLE")
  //   .value("CSR_HEX_CHANGE", CSR_HEX_CHANGE)
  //   .value("CSR_BIN_CHANGE", CSR_BIN_CHANGE)
  //   .value("CSR_FIELD_CHANGE", CSR_FIELD_CHANGE);

  value_object<csr_sstatus_str_t>("csr_sstatus_t")
  .field("sd", &csr_sstatus_str_t::sd)
  .field("rev0", &csr_sstatus_str_t::rev0)
  .field("uxl", &csr_sstatus_str_t::uxl)
  .field("rev1", &csr_sstatus_str_t::rev1)
  .field("mxr", &csr_sstatus_str_t::mxr)
  .field("sum", &csr_sstatus_str_t::sum)
  .field("rev2", &csr_sstatus_str_t::rev2)
  .field("xs", &csr_sstatus_str_t::xs)
  .field("fs", &csr_sstatus_str_t::fs)
  .field("rev3", &csr_sstatus_str_t::rev3)
  .field("vs", &csr_sstatus_str_t::vs)
  .field("spp", &csr_sstatus_str_t::spp)
  .field("rev4", &csr_sstatus_str_t::rev4)
  .field("ube", &csr_sstatus_str_t::ube)
  .field("spie", &csr_sstatus_str_t::spie)
  .field("rev5", &csr_sstatus_str_t::rev5)
  .field("sie", &csr_sstatus_str_t::sie)
  .field("rev6", &csr_sstatus_str_t::rev6)
  .field("hex", &csr_sstatus_str_t::hex)
  .field("bin", &csr_sstatus_str_t::bin);

  function("sstatus_handler", &sstatus_handler);
}