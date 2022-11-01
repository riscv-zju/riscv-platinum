#include <emscripten/bind.h>
#include <algorithm>
#include "utils.h"

using namespace emscripten;

struct csr_mstatus_str_t {
  std::string sd;
  std::string rev0;
  std::string mbe;
  std::string sbe;
  std::string sxl;
  std::string uxl;
  std::string rev1;
  std::string tsr;
  std::string tw;
  std::string tvm;
  std::string mxr;
  std::string sum;
  std::string mprv;
  std::string xs;
  std::string fs;
  std::string mpp;
  std::string vs;
  std::string spp;
  std::string mpie;
  std::string ube;
  std::string spie;
  std::string rev2;
  std::string mie;
  std::string rev3;
  std::string sie;
  std::string rev4;
  std::string hex;
  std::string bin;
};

struct csr_mstatus_t {
  unsigned char sd;
  unsigned long rev0;
  unsigned char mbe;
  unsigned char sbe;
  unsigned char sxl;
  unsigned char uxl;
  unsigned short rev1;
  unsigned char tsr;
  unsigned char tw;
  unsigned char tvm;
  unsigned char mxr;
  unsigned char sum;
  unsigned char mprv;
  unsigned char xs;
  unsigned char fs;
  unsigned char mpp;
  unsigned char vs;
  unsigned char spp;
  unsigned char mpie;
  unsigned char ube;
  unsigned char spie;
  unsigned char rev2;
  unsigned char mie;
  unsigned char rev3;
  unsigned char sie;
  unsigned char rev4;
};

reg_t field_to_reg (csr_mstatus_str_t& in) {
  // format field
  in.rev0 = "0";
  in.rev1 = "0";
  in.rev2 = "0";
  in.rev3 = "0";
  in.rev4 = "0";
  in.sd = in.sd.substr(0, std::min(1UL, in.sd.length()));
  in.mbe = in.mbe.substr(0, std::min(1UL, in.mbe.length()));
  in.sbe = in.sbe.substr(0, std::min(1UL, in.sbe.length()));
  in.sxl = in.sxl.substr(0, std::min(2UL, in.sxl.length()));
  in.uxl = in.uxl.substr(0, std::min(2UL, in.uxl.length()));
  in.tsr = in.tsr.substr(0, std::min(1UL, in.tsr.length()));
  in.tw = in.tw.substr(0, std::min(1UL, in.tw.length()));
  in.tvm = in.tvm.substr(0, std::min(1UL, in.tvm.length()));
  in.mxr = in.mxr.substr(0, std::min(1UL, in.mxr.length()));
  in.sum = in.sum.substr(0, std::min(1UL, in.sum.length()));
  in.mprv = in.mprv.substr(0, std::min(1UL, in.mprv.length()));
  in.xs = in.xs.substr(0, std::min(2UL, in.xs.length()));
  in.fs = in.fs.substr(0, std::min(2UL, in.fs.length()));
  in.mpp = in.mpp.substr(0, std::min(2UL, in.mpp.length()));
  in.vs = in.vs.substr(0, std::min(2UL, in.vs.length()));
  in.spp = in.spp.substr(0, std::min(1UL, in.spp.length()));
  in.mpie = in.mpie.substr(0, std::min(1UL, in.mpie.length()));
  in.ube = in.ube.substr(0, std::min(1UL, in.ube.length()));
  in.spie = in.spie.substr(0, std::min(1UL, in.spie.length()));
  in.mie = in.mie.substr(0, std::min(1UL, in.mie.length()));
  in.sie = in.sie.substr(0, std::min(1UL, in.sie.length()));

  csr_mstatus_t fields;
  fields.sd = std::stol(in.sd, 0, 2);
  fields.rev0 = std::stol(in.rev0, 0, 2);
  fields.mbe = std::stol(in.mbe, 0, 2);
  fields.sbe = std::stol(in.sbe, 0, 2);
  fields.sxl = std::stol(in.sxl, 0, 2);
  fields.uxl = std::stol(in.uxl, 0, 2);
  fields.rev1 = std::stol(in.rev1, 0, 2);
  fields.tsr = std::stol(in.tsr, 0, 2);
  fields.tw = std::stol(in.tw, 0, 2);
  fields.tvm = std::stol(in.tvm, 0, 2);
  fields.mxr = std::stol(in.mxr, 0, 2);
  fields.sum = std::stol(in.sum, 0, 2);
  fields.mprv = std::stol(in.mprv, 0, 2);
  fields.xs = std::stol(in.xs, 0, 2);
  fields.fs = std::stol(in.fs, 0, 2);
  fields.mpp = std::stol(in.mpp, 0, 2);
  fields.vs = std::stol(in.vs, 0, 2);
  fields.spp = std::stol(in.spp, 0, 2);
  fields.mpie = std::stol(in.mpie, 0, 2);
  fields.ube = std::stol(in.ube, 0, 2);
  fields.spie = std::stol(in.spie, 0, 2);
  fields.rev2 = std::stol(in.rev2, 0, 2);
  fields.mie = std::stol(in.mie, 0, 2);
  fields.rev3 = std::stol(in.rev3, 0, 2);
  fields.sie = std::stol(in.sie, 0, 2);
  fields.rev4   = std::stol(in.rev4, 0, 2);

  reg_t reg = 0ULL
    | TRUNC(fields.sd, 1) << 63
    | TRUNC(fields.rev0, 25) << 38
    | TRUNC(fields.mbe, 1) << 37
    | TRUNC(fields.sbe, 1) << 36
    | TRUNC(fields.sxl, 2) << 34 
    | TRUNC(fields.uxl, 2) << 32 
    | TRUNC(fields.rev1, 9) << 23 
    | TRUNC(fields.tsr, 1) << 22 
    | TRUNC(fields.tw, 1) << 21 
    | TRUNC(fields.tvm, 1) << 20 
    | TRUNC(fields.mxr, 1) << 19 
    | TRUNC(fields.sum, 1) << 18 
    | TRUNC(fields.mprv, 1) << 17 
    | TRUNC(fields.xs, 2) << 15 
    | TRUNC(fields.fs, 2) << 13 
    | TRUNC(fields.mpp, 2) << 11 
    | TRUNC(fields.vs, 2) << 9 
    | TRUNC(fields.spp, 1) << 8 
    | TRUNC(fields.mpie, 1) << 7 
    | TRUNC(fields.ube, 1) << 6 
    | TRUNC(fields.spie, 1) << 5 
    | TRUNC(fields.rev2, 1) << 4 
    | TRUNC(fields.mie, 1) << 3 
    | TRUNC(fields.rev3, 1) << 2
    | TRUNC(fields.sie, 1) << 1
    | TRUNC(fields.rev4, 1);

  return reg;
}

void reg_to_field (reg_t reg, csr_mstatus_str_t& in) {
  csr_mstatus_t fields;
  fields.sd = TRUNC(reg >> 63, 1);
  fields.rev0 = TRUNC(reg >> 38, 25);
  fields.mbe = TRUNC(reg >> 37, 1);
  fields.sbe = TRUNC(reg >> 36, 1);
  fields.sxl = TRUNC(reg >> 34, 2);
  fields.uxl = TRUNC(reg >> 32, 2);
  fields.rev1 = TRUNC(reg >> 23, 9);
  fields.tsr = TRUNC(reg >> 22, 1);
  fields.tw = TRUNC(reg >> 21, 1);
  fields.tvm = TRUNC(reg >> 20, 1);
  fields.mxr = TRUNC(reg >> 19, 1);
  fields.sum = TRUNC(reg >> 18, 1);
  fields.mprv = TRUNC(reg >> 17, 1);
  fields.xs = TRUNC(reg >> 15, 2);
  fields.fs = TRUNC(reg >> 13, 2);
  fields.mpp = TRUNC(reg >> 11, 2);
  fields.vs = TRUNC(reg >> 9, 2);
  fields.spp = TRUNC(reg >> 8, 1);
  fields.mpie = TRUNC(reg >> 7, 1);
  fields.ube = TRUNC(reg >> 6, 1);
  fields.spie = TRUNC(reg >> 5, 1);
  fields.rev2 = TRUNC(reg >> 4, 1);
  fields.mie = TRUNC(reg >> 3, 1);
  fields.rev3 = TRUNC(reg >> 2, 1);
  fields.sie = TRUNC(reg >> 1, 1);
  fields.rev4 = TRUNC(reg >> 0, 1);

  in.sd = tostring(fields.sd, 2, 1);
  in.rev0 = tostring(fields.rev0, 2, 25, true);
  in.mbe = tostring(fields.mbe, 2, 1);
  in.sbe = tostring(fields.sbe, 2, 1);
  in.sxl = tostring(fields.sxl, 2, 2);
  in.uxl = tostring(fields.uxl, 2, 2);
  in.rev1 = tostring(fields.rev1, 2, 9, true);
  in.tsr = tostring(fields.tsr, 2, 1);
  in.tw = tostring(fields.tw, 2, 1);
  in.tvm = tostring(fields.tvm, 2, 1);
  in.mxr = tostring(fields.mxr, 2, 1);
  in.sum = tostring(fields.sum, 2, 1);
  in.mprv = tostring(fields.mprv, 2, 1);
  in.xs = tostring(fields.xs, 2, 2);
  in.fs = tostring(fields.fs, 2, 2);
  in.mpp = tostring(fields.mpp, 2, 2);
  in.vs = tostring(fields.vs, 2, 2);
  in.spp = tostring(fields.spp, 2, 1);
  in.mpie = tostring(fields.mpie, 2, 1);
  in.ube = tostring(fields.ube, 2, 1);
  in.spie = tostring(fields.spie, 2, 1);
  in.rev2 = tostring(fields.rev2, 2, 1, true);
  in.mie = tostring(fields.mie, 2, 1);
  in.rev3 = tostring(fields.rev3, 2, 1, true);
  in.sie = tostring(fields.sie, 2, 1);
  in.rev4 = tostring(fields.rev4, 2, 1, true);
}

csr_mstatus_str_t mstatus_handler(csr_mstatus_str_t csr, handle_t h) {
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

EMSCRIPTEN_BINDINGS(mstatus_visual) {
  // enum_<handle_t>("HANDLE")
  //   .value("CSR_HEX_CHANGE", CSR_HEX_CHANGE)
  //   .value("CSR_BIN_CHANGE", CSR_BIN_CHANGE)
  //   .value("CSR_FIELD_CHANGE", CSR_FIELD_CHANGE);

  value_object<csr_mstatus_str_t>("csr_mstatus_t")
  .field("sd", &csr_mstatus_str_t::sd)
  .field("rev0", &csr_mstatus_str_t::rev0)
  .field("mbe", &csr_mstatus_str_t::mbe)
  .field("sbe", &csr_mstatus_str_t::sbe)
  .field("sxl", &csr_mstatus_str_t::sxl)
  .field("uxl", &csr_mstatus_str_t::uxl)
  .field("rev1", &csr_mstatus_str_t::rev1)
  .field("tsr", &csr_mstatus_str_t::tsr)
  .field("tw", &csr_mstatus_str_t::tw)
  .field("tvm", &csr_mstatus_str_t::tvm)
  .field("mxr", &csr_mstatus_str_t::mxr)
  .field("sum", &csr_mstatus_str_t::sum)
  .field("mprv", &csr_mstatus_str_t::mprv)
  .field("xs", &csr_mstatus_str_t::xs)
  .field("fs", &csr_mstatus_str_t::fs)
  .field("mpp", &csr_mstatus_str_t::mpp)
  .field("vs", &csr_mstatus_str_t::vs)
  .field("spp", &csr_mstatus_str_t::spp)
  .field("mpie", &csr_mstatus_str_t::mpie)
  .field("ube", &csr_mstatus_str_t::ube)
  .field("spie", &csr_mstatus_str_t::spie)
  .field("rev2", &csr_mstatus_str_t::rev2)
  .field("mie", &csr_mstatus_str_t::mie)
  .field("rev3", &csr_mstatus_str_t::rev3)
  .field("sie", &csr_mstatus_str_t::sie)
  .field("rev4", &csr_mstatus_str_t::rev4)
  .field("hex", &csr_mstatus_str_t::hex)
  .field("bin", &csr_mstatus_str_t::bin);

  function("mstatus_handler", &mstatus_handler);
}