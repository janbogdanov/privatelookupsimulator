#include "gf2_ops.h"

#include <cstdlib>

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
    uint8_t e = 254;
    uint8_t i = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            i = gf2_mul(i, a);
        }
        e = e >> 1;
        a = gf2_mul(a, a);
    }
    return i;
}

gf2to8_t gf2_pwr (gf2to8_t a, uint32_t p) {
    if (a == 0) {
        return 0;
    }
    else if (p == 0) {
        return 1;
    }
    uint8_t i = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            i = gf2_mul(i, a);
        }
        p = p >> 1;
        a = gf2_mul(a, a);
    }
    return i;
}

/*gf2to8_t element_n(uint32_t a) {
    return a & 255;
}*/

void gf2_random(gf2to8_t& a) {
    // TODO Change to use C++11 random number generator

    //a = rand () % 256;
    a = 0;
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
    uint32_t e = 4294967294;
    uint32_t i = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            i = gf2_mul(i, a);
        }
        e = e >> 1;
        a = gf2_mul(a, a);
    }
    return i;
}

gf2to32_t gf2_pwr (gf2to32_t a, uint32_t p) {
    if (a == 0) {
        return 0;
    }
    else if (p == 0) {
        return 1;
    }
    uint32_t i = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            i = gf2_mul(i, a);
        }
        p = p >> 1;
        a = gf2_mul(a, a);
    }
    return i;
}

gf2to32_t element_n (uint32_t a) {
    return a & 4294967295;
}

void gf2_random(gf2to32_t& a) {
    // TODO Change to use C++11 random number generator

    a = rand () % (1 << 31);
}

uint32_t gf2_val (gf2to32_t a) {
    // if gf2to32_t == uint32_t then nothing to do
    return (uint32_t)a;
}
