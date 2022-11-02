#include <emscripten/bind.h>
#include <algorithm>
#include "utils.h"

using namespace emscripten;

struct csr_medeleg_str_t {
  std::string rev0;
  std::string store_page_fault;
  std::string rev1;
  std::string load_page_fault;
  std::string fetch_page_fault;
  std::string machine_ecall;
  std::string rev2;
  std::string supervisor_ecall;
  std::string user_ecall;
  std::string store_access;
  std::string misaligned_store;
  std::string load_access;
  std::string misaligned_load;
  std::string breakpoint;
  std::string illegal_instruction;
  std::string fetch_access;
  std::string misaligned_fetch;
  std::string hex;
  std::string bin;
};

struct csr_medeleg_t {
  unsigned long long rev0;
  unsigned char store_page_fault;
  unsigned char rev1;
  unsigned char load_page_fault;
  unsigned char fetch_page_fault;
  unsigned char machine_ecall;
  unsigned char rev2;
  unsigned char supervisor_ecall;
  unsigned char user_ecall;
  unsigned char store_access;
  unsigned char misaligned_store;
  unsigned char load_access;
  unsigned char misaligned_load;
  unsigned char breakpoint;
  unsigned char illegal_instruction;
  unsigned char fetch_access;
  unsigned char misaligned_fetch;
};

reg_t field_to_reg (csr_medeleg_str_t& in) {
  // format field
  in.rev0 = "0";
  in.rev1 = "0";
  in.rev2 = "0";
  in.store_page_fault = in.store_page_fault.substr(0, std::min(1UL, in.store_page_fault.length()));
  in.load_page_fault = in.load_page_fault.substr(0, std::min(1UL, in.load_page_fault.length()));
  in.fetch_page_fault = in.fetch_page_fault.substr(0, std::min(1UL, in.fetch_page_fault.length()));
  in.machine_ecall = in.machine_ecall.substr(0, std::min(1UL, in.machine_ecall.length()));
  in.supervisor_ecall = in.supervisor_ecall.substr(0, std::min(1UL, in.supervisor_ecall.length()));
  in.user_ecall = in.user_ecall.substr(0, std::min(1UL, in.user_ecall.length()));
  in.store_access = in.store_access.substr(0, std::min(1UL, in.store_access.length()));
  in.misaligned_store = in.misaligned_store.substr(0, std::min(1UL, in.misaligned_store.length()));
  in.load_access = in.load_access.substr(0, std::min(1UL, in.load_access.length()));
  in.misaligned_load = in.misaligned_load.substr(0, std::min(1UL, in.misaligned_load.length()));
  in.breakpoint = in.breakpoint.substr(0, std::min(1UL, in.breakpoint.length()));
  in.illegal_instruction = in.illegal_instruction.substr(0, std::min(1UL, in.illegal_instruction.length()));
  in.fetch_access = in.fetch_access.substr(0, std::min(1UL, in.fetch_access.length()));
  in.misaligned_fetch = in.misaligned_fetch.substr(0, std::min(1UL, in.misaligned_fetch.length()));

  csr_medeleg_t fields;
  fields.rev0 = std::stol(in.rev0, 0, 2);
  fields.store_page_fault = std::stol(in.store_page_fault, 0, 2);
  fields.rev1 = std::stol(in.rev1, 0, 2);
  fields.load_page_fault = std::stol(in.load_page_fault, 0, 2);
  fields.fetch_page_fault = std::stol(in.fetch_page_fault, 0, 2);
  fields.machine_ecall = std::stol(in.machine_ecall, 0, 2);
  fields.rev2 = std::stol(in.rev2, 0, 2);
  fields.supervisor_ecall = std::stol(in.supervisor_ecall, 0, 2);
  fields.user_ecall = std::stol(in.user_ecall, 0, 2);
  fields.store_access = std::stol(in.store_access, 0, 2);
  fields.misaligned_store = std::stol(in.misaligned_store, 0, 2);
  fields.load_access = std::stol(in.load_access, 0, 2);
  fields.misaligned_load = std::stol(in.misaligned_load, 0, 2);
  fields.breakpoint = std::stol(in.breakpoint, 0, 2);
  fields.illegal_instruction = std::stol(in.illegal_instruction, 0, 2);
  fields.fetch_access = std::stol(in.fetch_access, 0, 2);
  fields.misaligned_fetch = std::stol(in.misaligned_fetch, 0, 2);

  reg_t reg = 0ULL
    | TRUNC(fields.rev0, 48) << 16
    | TRUNC(fields.store_page_fault, 1) << 15
    | TRUNC(fields.rev1, 1) << 14
    | TRUNC(fields.load_page_fault, 1) << 13
    | TRUNC(fields.fetch_page_fault, 1) << 12
    | TRUNC(fields.machine_ecall, 1) << 11
    | TRUNC(fields.rev2, 1) << 10
    | TRUNC(fields.supervisor_ecall, 1) << 9
    | TRUNC(fields.user_ecall, 1) << 8
    | TRUNC(fields.store_access, 1) << 7
    | TRUNC(fields.misaligned_store, 1) << 6
    | TRUNC(fields.load_access, 1) << 5
    | TRUNC(fields.misaligned_load, 1) << 4
    | TRUNC(fields.breakpoint, 1) << 3
    | TRUNC(fields.illegal_instruction, 1) << 2
    | TRUNC(fields.fetch_access, 1) << 1
    | TRUNC(fields.misaligned_fetch, 1);

  return reg;
}

void reg_to_field (reg_t reg, csr_medeleg_str_t& in) {
  csr_medeleg_t fields;
  fields.rev0 = TRUNC(reg >> 16, 48);
  fields.store_page_fault = TRUNC(reg >> 15, 1);
  fields.rev1 = TRUNC(reg >> 14, 1);
  fields.load_page_fault = TRUNC(reg >> 13, 1);
  fields.fetch_page_fault = TRUNC(reg >> 12, 1);
  fields.machine_ecall = TRUNC(reg >> 11, 1);
  fields.rev2 = TRUNC(reg >> 10, 1);
  fields.supervisor_ecall = TRUNC(reg >> 9, 1);
  fields.user_ecall = TRUNC(reg >> 8, 1);
  fields.store_access = TRUNC(reg >> 7, 1);
  fields.misaligned_store = TRUNC(reg >> 6, 1);
  fields.load_access = TRUNC(reg >> 5, 1);
  fields.misaligned_load = TRUNC(reg >> 4, 1);
  fields.breakpoint = TRUNC(reg >> 3, 1);
  fields.illegal_instruction = TRUNC(reg >> 2, 1);
  fields.fetch_access = TRUNC(reg >> 1, 1);
  fields.misaligned_fetch = TRUNC(reg >> 0, 1);

  in.rev0 = tostring(fields.rev0, 2, 48, true);
  in.store_page_fault = tostring(fields.store_page_fault, 2, 1);
  in.rev1 = tostring(fields.rev1, 2, 1, true);
  in.load_page_fault = tostring(fields.load_page_fault, 2, 1);
  in.fetch_page_fault = tostring(fields.fetch_page_fault, 2, 1);
  in.machine_ecall = tostring(fields.machine_ecall, 2, 1);
  in.rev2 = tostring(fields.rev2, 2, 1, true);
  in.supervisor_ecall = tostring(fields.supervisor_ecall, 2, 1);
  in.user_ecall = tostring(fields.user_ecall, 2, 1);
  in.store_access = tostring(fields.store_access, 2, 1);
  in.misaligned_store = tostring(fields.misaligned_store, 2, 1);
  in.load_access = tostring(fields.load_access, 2, 1);
  in.misaligned_load = tostring(fields.misaligned_load, 2, 1);
  in.breakpoint = tostring(fields.breakpoint, 2, 1);
  in.illegal_instruction = tostring(fields.illegal_instruction, 2, 1);
  in.fetch_access = tostring(fields.fetch_access, 2, 1);
  in.misaligned_fetch = tostring(fields.misaligned_fetch, 2, 1);
}

csr_medeleg_str_t medeleg_handler(csr_medeleg_str_t csr, handle_t h) {
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

EMSCRIPTEN_BINDINGS(medeleg_visual) {
  value_object<csr_medeleg_str_t>("csr_medeleg_t")
  .field("rev0", &csr_medeleg_str_t::rev0)
  .field("store_page_fault", &csr_medeleg_str_t::store_page_fault)
  .field("rev1", &csr_medeleg_str_t::rev1)
  .field("load_page_fault", &csr_medeleg_str_t::load_page_fault)
  .field("fetch_page_fault", &csr_medeleg_str_t::fetch_page_fault)
  .field("machine_ecall", &csr_medeleg_str_t::machine_ecall)
  .field("rev2", &csr_medeleg_str_t::rev2)
  .field("supervisor_ecall", &csr_medeleg_str_t::supervisor_ecall)
  .field("user_ecall", &csr_medeleg_str_t::user_ecall)
  .field("store_access", &csr_medeleg_str_t::store_access)
  .field("misaligned_store", &csr_medeleg_str_t::misaligned_store)
  .field("load_access", &csr_medeleg_str_t::load_access)
  .field("misaligned_load", &csr_medeleg_str_t::misaligned_load)
  .field("breakpoint", &csr_medeleg_str_t::breakpoint)
  .field("illegal_instruction", &csr_medeleg_str_t::illegal_instruction)
  .field("fetch_access", &csr_medeleg_str_t::fetch_access)
  .field("misaligned_fetch", &csr_medeleg_str_t::misaligned_fetch)
  .field("hex", &csr_medeleg_str_t::hex)
  .field("bin", &csr_medeleg_str_t::bin);

  function("medeleg_handler", &medeleg_handler);
}