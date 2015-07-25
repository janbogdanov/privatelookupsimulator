#include "gf2_ops.h"

// 8-bit variants
gf2to8_t gf2_new (uint8_t a) {
    // if gf2to8_t == uint8_t then nothing to do
    return (gf2to8_t)a;
}

gf2to8_t gf2_add (gf2to8_t a, gf2to8_t b) {
    // TODO
}

gf2to8_t gf2_mul (gf2to8_t a, gf2to8_t b) {
    // TODO
}

gf2to8_t gf2_inv (gf2to8_t a) {
    // TODO
}

uint8_t gf2_val (gf2to8_t a) {
    // if gf2to8_t == uint8_t then nothing to do
    return (uint8_t)a;
}

// 32-bit variants
gf2to32_t gf2_new (uint32_t a) {
    // if gf2to32_t == uint32_t then nothing to do
    return (gf2to32_t)a;
}

gf2to32_t gf2_add (gf2to32_t a, gf2to32_t b) {
    // TODO
}

gf2to32_t gf2_mul (gf2to32_t a, gf2to32_t b) {
    // TODO
}

gf2to32_t gf2_inv (gf2to32_t a) {
    // TODO
}

uint32_t gf2_val (gf2to32_t a) {
    // if gf2to32_t == uint32_t then nothing to do
    return (uint32_t)a;
}
