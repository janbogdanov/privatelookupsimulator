#include "gf2_ops.h"

// 8-bit variants
gf2to8_t gf2_new (uint8_t a) {
    // if gf2to8_t == uint8_t then nothing to do
    return (gf2to8_t)a;
}

gf2to8_t gf2_add (gf2to8_t a, gf2to8_t b) {
    return a ^ b;
}

gf2to8_t gf2_mul (gf2to8_t a, gf2to8_t b) {
    uint8_t c = 0;
    uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        if (b & 1) {
            c ^= a;
            }
        if (a & 0b10000000) {
            a <<= 1;
            a ^= 0b100011101;
            }
        else {
            a <<=1;
        }
        b >>= 1;
        }
    return c;
}

gf2to8_t gf2_inv (gf2to8_t a) {
    if (a == 0) {
        return 0;
    }
    uint8_t i = a;
    while (gf2_mul (a, i) != 1) {
        i++;
    }
    return i;
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
    return a ^ b;
}

gf2to32_t gf2_mul (gf2to32_t a, gf2to32_t b) {
    uint32_t c = 0;
    uint8_t i = 0;
    for (i = 0; i < 32; i++) {
        if (b & 1) {
            c ^= a;
            }
        if (a & 0x80000000) {
            a <<= 1;
            a ^= 0x100400007;
            }
        else {
            a <<=1;
        }
        b >>= 1;
        }
    return c;
}

gf2to32_t gf2_inv (gf2to32_t a) {
    if (a == 0) {
        return 0;
    }
    uint32_t i = a;
    while (gf2_mul (a, i) != 1) {
        i++;
    }
    return i;
}

uint32_t gf2_val (gf2to32_t a) {
    // if gf2to32_t == uint32_t then nothing to do
    return (uint32_t)a;
}
