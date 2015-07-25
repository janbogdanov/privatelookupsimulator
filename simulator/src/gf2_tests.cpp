#include <iostream>
#include "gf2_ops.h"
using namespace std;

bool test_gf2to8_addition (uint8_t addend1, uint8_t addend2, uint8_t expected_sum) {

    cout << "Testing 8-bit gf2_add (" << (uint32_t)addend1 << ", " << (uint32_t)addend2 << ") ... ";

    // Convert inputs
    gf2to8_t a1 = gf2_new(addend1);
    gf2to8_t a2 = gf2_new(addend2);
    // Add
    gf2to8_t sum = gf2_add (a1, a2);
    // Compare
    uint8_t result = gf2_val (sum);

    if (result == expected_sum) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_sum << ")" << endl;
        return false;
    }
}

bool test_gf2to8_arithmetic () {

    bool success = false;

    // Addition tests
    success = test_gf2to8_addition(0, 0, 0);
    success &= test_gf2to8_addition(0, 1, 1);
    success &= test_gf2to8_addition(1, 0, 1);
    // TODO: add more values

    // TODO: add multiplication tests

    // TODO: add inversion tests

    return success;
}

bool test_gf2to32_arithmetic () {

    // TODO: add tests for 32-bit versions, following logic from above function

    return false;
}
