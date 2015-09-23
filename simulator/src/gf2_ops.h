#ifndef GF2_OPS_H
#define GF2_OPS_H

#include <inttypes.h>
#include <vector>

// Currently, we're using simple uint types to represent GF_2**X values
typedef uint8_t gf2to8_t;
typedef uint32_t gf2to32_t;

// 8-bit variants
gf2to8_t gf2_new (uint8_t a);
gf2to8_t gf2_add (gf2to8_t a, gf2to8_t b);
gf2to8_t gf2_mul (gf2to8_t a, gf2to8_t b);
gf2to8_t gf2_inv (gf2to8_t a);
gf2to8_t gf2_pwr (gf2to8_t a, uint32_t p);
gf2to8_t element_n (uint8_t a);
std::vector<gf2to8_t> element_nvector(std::vector<uint8_t> a);
void gf2_random (gf2to8_t& a);
uint8_t gf2_val (gf2to8_t a);

// 32-bit variants
gf2to32_t gf2_new (uint32_t a);
gf2to32_t gf2_add (gf2to32_t a, gf2to32_t b);
gf2to32_t gf2_mul (gf2to32_t a, gf2to32_t b);
gf2to32_t gf2_inv (gf2to32_t a);
gf2to32_t gf2_pwr (gf2to32_t a, uint32_t p);
gf2to32_t element_n (uint32_t a);
std::vector<gf2to32_t> element_nvector(std::vector<uint32_t> a);
void gf2_random (gf2to32_t& a);
uint32_t gf2_val (gf2to32_t a);

#endif // GF2_OPS_H

