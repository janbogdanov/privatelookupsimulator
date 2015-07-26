#include <iostream>
#include "secshare.h"
using namespace std;

bool test_uint8_scalar_sharing (uint8_t value) {

    cout << "Testing 8-bit share on a scalar (" << (uint32_t)value << ") ... ";

    // Declare variables
    shared_uint8_t share1a {0}, share2a {0}, share3a {0};
    bool success_a = share (value, share1a, share2a, share3a);

    if (!success_a) {
        cout << "FAILED! (First sharing failed.)" << endl;
        return false;
    }

    // Make second sharing to test reuse of randomness
    shared_uint8_t share1b {0}, share2b {0}, share3b {0};
    bool success_b = share (value, share1b, share2b, share3b);

    if (!success_b) {
        cout << "FAILED! (Second sharing failed.)" << endl;
        return false;
    }

    // This catches only the trivial randomness reuse, but it will do for now
    if (share1a == share1b && share2a == share2b && share3a == share3b) {
        cout << "FAILED! (Randomness reuse over two subsequent sharings.)" << endl;
        return false;
    }

    // Reconstruct
    uint8_t result {0};
    bool rec_success = reconstruct (share1a, share2a, share3a, result);

    if (!rec_success) {
        cout << "FAILED! (Reconstruction failed.)" << endl;
        return false;
    }

    if (value != result) {
        cout << "FAILED! (Reconstruction yielded wrong value: " << result << ", expected " << value << ".)" << endl;
        return false;
    }

    cout << "OK" << endl;
    return true;
}

bool test_uint8_vector_sharing (const std::vector<uint8_t> &values) {

    cout << "Testing 8-bit share on a vector of " << values.size() << " values ... ";

    // Declare variables
    // Note that this does not test for wrongly sized input share vectors
    std::vector<shared_uint8_t> shares1a (values.size (), 0), shares2a (values.size (), 0), shares3a (values.size (), 0);
    bool success_a = share (values, shares1a, shares2a, shares3a);

    if (!success_a) {
        cout << "FAILED! (First sharing failed.)" << endl;
        return false;
    }

    if (shares1a.size () != values.size()) {
        cout << "FAILED! (Share vector 1 has incorrect size: " << shares1a.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    if (shares2a.size () != values.size()) {
        cout << "FAILED! (Share vector 2 has incorrect size: " << shares2a.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    if (shares3a.size () != values.size()) {
        cout << "FAILED! (Share vector 3 has incorrect size: " << shares3a.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    // Make second sharing to test reuse of randomness
    std::vector<shared_uint8_t> shares1b (values.size (), 0), shares2b (values.size (), 0), shares3b (values.size (), 0);
    bool success_b = share (values, shares1b, shares2b, shares3b);

    if (!success_b) {
        cout << "FAILED! (Second sharing failed.)" << endl;
        return false;
    }

    if (shares1b.size () != values.size()) {
        cout << "FAILED! (Share vector 1 has incorrect size: " << shares1b.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    if (shares2b.size () != values.size()) {
        cout << "FAILED! (Share vector 2 has incorrect size: " << shares2b.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    if (shares3b.size () != values.size()) {
        cout << "FAILED! (Share vector 3 has incorrect size: " << shares3b.size() << ", should be " << values.size() << ")" << endl;
        return false;
    }

    // This catches only the trivial randomness reuse, but it will do for now
    bool equal = true;
    for (size_t i = 0; i < values.size(); i++) {
        if (shares1a[i] != shares1b[i] || shares2a[i] != shares2b[i] || shares3a[i] != shares3b[i])
            equal = false;
    }

    if (equal) {
        cout << "FAILED! (Randomness reuse over two subsequent sharings.)" << endl;
        return false;
    }

    // Reconstruct
    std::vector<uint8_t> results (values.size(), 0);
    bool rec_success = reconstruct (shares1a, shares2a, shares3a, results);

    if (!rec_success) {
        cout << "FAILED! (Reconstruction failed.)" << endl;
        return false;
    }

    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] != results[i]) {
            cout << "FAILED! (Reconstruction yielded wrong value at index " << i << ": " << results[i] << ", expected " << values[i] << ".)" << endl;
            return false;
        }
    }

    cout << "OK" << endl;
    return true;
}

bool test_uint32_scalar_sharing (uint8_t value) {
    // TODO
    return false;
}

bool test_uint32_vector_sharing (const std::vector<uint8_t> &values) {
    // TODO
    return false;
}

bool test_8bit_secret_sharing () {

    bool success = false;

    // Scalar tests
    success = test_uint32_scalar_sharing(0);
    success &= test_uint32_scalar_sharing(1);
    // ...

    // Vector tests
    success &= test_uint32_vector_sharing(std::vector<uint8_t> {0, 0});
    success &= test_uint32_vector_sharing(std::vector<uint8_t> {0, 1});
    success &= test_uint32_vector_sharing(std::vector<uint8_t> {1, 1});
    success &= test_uint32_vector_sharing(std::vector<uint8_t> {0, 1, 2, 3, 4, 5, 6 , 7, 8, 9});
    // ...

    return success;
}

bool test_32bit_secret_sharing () {
    // TODO
    return false;
}
