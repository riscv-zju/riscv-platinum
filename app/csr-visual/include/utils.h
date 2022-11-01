#ifndef _CSR_VISUAL_UTILS_H
#define _CSR_VISUAL_UTILS_H

#include <string>

typedef unsigned long long int reg_t;

#define MASK(width) ((1ULL << width)-1)
#define TRUNC(val, width) (val & MASK(width))

enum handle_t {
    CSR_HEX_CHANGE,
    CSR_BIN_CHANGE,
    CSR_FIELD_CHANGE
};

std::string tostring(reg_t n, int base, int width, bool zero=false);

#endif