#include "lookup_tests.h"
#include "lookup.h"
#include "secshare.h"
#include <vector>
#include <iostream>
using namespace std;

bool test_8bit_single_index_lookup (std::vector<uint8_t> array, size_t index) {

    const size_t array_size = array.size();

    cout << "Testing 8-bit private lookup with index " << index<< " on a vector of " << array_size << " values ... ";

    // Declare three computing parties
    computing_party_state<shared_uint8_t, uint8_t> party1, party2, party3;

    // Share the secret vector
    party1.v.resize (array_size);
    party2.v.resize (array_size);
    party3.v.resize (array_size);
    if (!share (array, party1.v, party2.v, party3.v)) {
        cout << "FAILED! (Secret sharing of vector failed.)" << endl;
        return false;
    }

    // Share the index
    if (!share (index, party1.j, party2.j, party3.j)) {
        cout << "FAILED! (Secret sharing of index failed.)" << endl;
        return false;
    }

    // Run the lookup
    if (!lookup (party1, party2, party3)) {
        cout << "FAILED! (Lookup protocol failed.)" << endl;
        return false;
    }

    // Reconstruct the result element
    uint8_t element = 0;
    if (!reconstruct (party1.w, party2.w, party3.w, element)) {
        cout << "FAILED! (Result reconstruction failed.)" << endl;
        return false;
    }

    // Check correctness of result
    if (element != array[index]) {
        cout << "FAILED! (Lookup result wrong: " << element << ", expected " << array[index] << ".)" << endl;
        return false;
    }

    cout << "OK" << endl;
    return true;
}


bool test_8bit_private_lookup () {

    bool success = false;

    // Scalar tests
   // success = test_8bit_single_index_lookup({1, 2}, 0);
   // success &= test_8bit_single_index_lookup({2, 3}, 0);
    success &= test_8bit_single_index_lookup({2, 3}, 1);
   // success &= test_8bit_single_index_lookup({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5);
    // ...

    return success;
}

bool test_32bit_private_lookup () {
    // TODO
    return false;
}


