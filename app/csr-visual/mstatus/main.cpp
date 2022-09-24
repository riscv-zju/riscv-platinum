#include <emscripten/bind.h>
#include <algorithm>

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
};

struct csr_mstatus_t {
  unsigned long int sd;
  unsigned long int rev0;
  unsigned long int mbe;
  unsigned long int sbe;
  unsigned long int sxl;
  unsigned long int uxl;
  unsigned long int rev1;
  unsigned long int tsr;
  unsigned long int tw;
  unsigned long int tvm;
  unsigned long int mxr;
  unsigned long int sum;
  unsigned long int mprv;
  unsigned long int xs;
  unsigned long int fs;
  unsigned long int mpp;
  unsigned long int vs;
  unsigned long int spp;
  unsigned long int mpie;
  unsigned long int ube;
  unsigned long int spie;
  unsigned long int rev2;
  unsigned long int mie;
  unsigned long int rev3;
  unsigned long int sie;
  unsigned long int rev4;
};


struct hex_bin_t {
  std::string hex;
  std::string bin;
};

std::string dump_csr_mastatus(csr_mstatus_str_t csr) {
  printf("Hello in wasm\n");
  return "Hello from wasm\n";
}

std::string tostring(unsigned long int n, int base) {
  std::string s = "";
  do {
    int bit = n % base;
    if (bit > 9)
      s.insert(0, 1, ('a' + bit - 10));
    else
      s.insert(0, 1, ('0' + bit));
    n = n / base;
  } while(n != 0);
  return s;
}

hex_bin_t from_field(csr_mstatus_str_t in) {
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

  unsigned long csr = 0 | (fields.sd << 63);
  printf("%lx\n", csr);
  printf("%lx %lx %lx %lx\n", csr, fields.rev0, fields.rev0 << 38, csr | (fields.rev0 << 38));
  csr = csr | (fields.rev0 << 38);
    //  |
    // fields.mbe << 37 |
    // fields.sbe << 36;
  printf("%lx %lx %lx\n", csr, fields.rev0, fields.rev0 << 38);

  csr = csr |
    fields.sxl << 34 |
    fields.uxl << 32 |
    fields.rev1 << 23 |
    fields.tsr << 22 |
    fields.tw << 21 |
    fields.tvm << 20 |
    fields.mxr << 19 |
    fields.sum << 18 |
    fields.mprv << 17 |
    fields.xs << 15 |
    fields.fs << 13 |
    fields.mpp << 11 |
    fields.vs << 9 |
    fields.spp << 8 |
    fields.mpie << 7 |
    fields.ube << 6 |
    fields.spie << 5 |
    fields.rev2 << 4 |
    fields.mie << 3 |
    fields.rev3 << 2;
  
  printf("%lx\n", csr);  
  
  csr = csr |
    fields.sie << 1 |
    fields.rev4;

  printf("%lx\n", csr);

  hex_bin_t ret;
  ret.bin = tostring(csr, 2);
  ret.hex = tostring(csr, 16);

  return ret;
}



EMSCRIPTEN_BINDINGS(my_module) {
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
  .field("rev4", &csr_mstatus_str_t::rev4);

  value_object<hex_bin_t>("hex_bin_t")
  .field("hex", &hex_bin_t::hex)
  .field("bin", &hex_bin_t::bin);

  function("dump_csr_mastatus", &dump_csr_mastatus);
  function("from_field", &from_field);
}