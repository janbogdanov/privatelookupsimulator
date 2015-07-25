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

bool test_gf2to8_multiplication(uint8_t multiplicand1, uint8_t multiplicand2, uint8_t expected_product) {

    cout << "Testing 8-bit gf2_mul (" << (uint32_t)multiplicand1 << ", " << (uint32_t)multiplicand2 << ") ... ";

    // Convert inputs
    gf2to8_t a1 = gf2_new(multiplicand1);
    gf2to8_t a2 = gf2_new(multiplicand2);
    // Multiply
    gf2to8_t product = gf2_mul (a1, a2);
    // Compare
    uint8_t result = gf2_val (product);

    if (result == expected_product) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_product << ")" << endl;
        return false;
    }
}

bool test_gf2to8_inversion(uint8_t invertible, uint8_t expected_inverse) {

    cout << "Testing 8-bit gf2_inv (" << (uint32_t)invertible << ") ... ";

    // Convert inputs
    gf2to8_t a1 = gf2_new(invertible);
    // Multiply
    gf2to8_t inverse = gf2_inv (a1);
    // Compare
    uint8_t result = gf2_val (inverse);

    if (result == expected_inverse) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_inverse << ")" << endl;
        return false;
    }
}

bool test_gf2to32_addition (uint32_t addend1, uint32_t addend2, uint32_t expected_sum) {

    cout << "Testing 32-bit gf2_add (" << (uint32_t)addend1 << ", " << (uint32_t)addend2 << ") ... ";

    // Convert inputs
    gf2to32_t a1 = gf2_new(addend1);
    gf2to32_t a2 = gf2_new(addend2);
    // Add
    gf2to32_t sum = gf2_add (a1, a2);
    // Compare
    uint32_t result = gf2_val (sum);

    if (result == expected_sum) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_sum << ")" << endl;
        return false;
    }
}

bool test_gf2to32_multiplication(uint32_t multiplicand1, uint32_t multiplicand2, uint32_t expected_product) {

    cout << "Testing 32-bit gf2_mul (" << (uint32_t)multiplicand1 << ", " << (uint32_t)multiplicand2 << ") ... ";

    // Convert inputs
    gf2to32_t a1 = gf2_new(multiplicand1);
    gf2to32_t a2 = gf2_new(multiplicand2);
    // Multiply
    gf2to32_t product = gf2_mul (a1, a2);
    // Compare
    uint32_t result = gf2_val (product);

    if (result == expected_product) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_product << ")" << endl;
        return false;
    }
}

bool test_gf2to32_inversion(uint32_t invertible, uint32_t expected_inverse) {

    cout << "Testing 32-bit gf2_inv (" << (uint32_t)invertible << ") ... ";

    // Convert inputs
    gf2to32_t a1 = gf2_new(invertible);
    // Multiply
    gf2to32_t inverse = gf2_inv (a1);
    // Compare
    uint32_t result = gf2_val (inverse);

    if (result == expected_inverse) {
        cout << "OK" << endl;
        return true;
    } else {
        cout << "FAILED! (Was " << (uint32_t)result << ", should be " << (uint32_t)expected_inverse << ")" << endl;
        return false;
    }
}

bool test_gf2to8_arithmetic () {

    bool success = false;

    // Addition tests
    success = test_gf2to8_addition(0, 0, 0);
    success &= test_gf2to8_addition(0, 1, 1);
    success &= test_gf2to8_addition(1, 0, 1);
    success &= test_gf2to8_addition(1, 1, 0);
    success &= test_gf2to8_addition(8, 42, 34);
    success &= test_gf2to8_addition(42, 8, 34);

    // Multiplication tests
    success &= test_gf2to8_multiplication(0, 0, 0);
    success &= test_gf2to8_multiplication(1, 0, 0);
    success &= test_gf2to8_multiplication(0, 1, 0);
    success &= test_gf2to8_multiplication(1, 1, 1);
    success &= test_gf2to8_multiplication(10, 10, 68);
    success &= test_gf2to8_multiplication(255, 255, 226);

    // Inversion tests
    success &= test_gf2to8_inversion(10, 221);
    success &= test_gf2to8_inversion(221, 10);
    success &= test_gf2to8_inversion(255, 253);
    success &= test_gf2to8_inversion(0, 0);
    success &= test_gf2to8_inversion(1, 1);

    return success;
}

bool test_gf2to32_arithmetic () {

    bool success = false;

    // Addition tests
    success = test_gf2to32_addition(0, 0, 0);
    success &= test_gf2to32_addition(1, 0, 1);
    success &= test_gf2to32_addition(0, 1, 1);
    success &= test_gf2to32_addition(1, 1, 0);
    success &= test_gf2to32_addition(4294967295, 4294967295, 0);

    // Multiplication tests
    success &= test_gf2to32_multiplication(0, 0, 0);
    success &= test_gf2to32_multiplication(0, 1, 0);
    success &= test_gf2to32_multiplication(1, 0, 0);
    success &= test_gf2to32_multiplication(1, 1, 1);
    success &= test_gf2to32_multiplication(4294967295, 4294967295, 2866106366);

    // Inversion tests
    success &= test_gf2to32_inversion(10, 3579838466);
    success &= test_gf2to32_inversion(0, 0);
    success &= test_gf2to32_inversion(1, 1);

    return success;
}
