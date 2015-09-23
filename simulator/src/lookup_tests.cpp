#include "lookup_tests.h"
#include "lookup.h"
#include "secshare.h"
#include <vector>
#include <iostream>
using namespace std;

/*bool test_8bit_single_index_lookup (std::vector<uint8_t> array, size_t index) {

    const size_t array_size = array.size();

    cout << "Testing 8-bit private lookup with index " << index << " on a vector of " << array_size << " values ... ";

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
    if (!share (element_n((uint8_t)(index + 1)), party1.j, party2.j, party3.j)) {
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
        cout << "FAILED! (Lookup result wrong: " << (uint32_t)element << ", expected " << (uint32_t)array[index] << ".)" << endl;
        return false;
    }

    cout << "OK" << endl;
    return true;
    }*/

bool test_8bit_multiple_index_lookup (std::vector<uint8_t> array, std::vector<uint8_t> index) {

    const size_t array_size = array.size();
    const size_t index_size = index.size();


    cout << "Testing 8-bit private lookup with " << index_size << " indices on a vector of " << array_size << " values ... ";

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
    party1.j.resize(index_size);
    party2.j.resize(index_size);
    party3.j.resize(index_size);
    std::vector<uint8_t> index2;
    index2.resize(index_size);
    for (uint32_t i = 0; i < index_size; i++) {
        index2[i] = index[i] + 1;
    }
    if (!share (element_nvector(index2), party1.j, party2.j, party3.j)) {
        cout << "FAILED! (Secret sharing of index failed.)" << endl;
        return false;
    }
    // Run the lookup
    if (!lookup (party1, party2, party3)) {
        cout << "FAILED! (Lookup protocol failed.)" << endl;
        return false;
    }

    // Reconstruct the result element
    //uint8_t element = 0;
    std::vector<uint8_t> element;
    element.resize(party1.w.size());
    if (!reconstruct (party1.w, party2.w, party3.w, element)) {
        cout << "FAILED! (Result reconstruction failed.)" << endl;
        return false;
    }

    // Check correctness of result
    for (uint32_t i = 0; i < index_size; i++) {
        if (element[i] != array[index[i]]) {
            cout << "FAILED! (Lookup result wrong: " << (uint32_t)element[i] << ", expected " << (uint32_t)array[index[i]] << ".)" << endl;
            return false;
        }
    }
    cout << "OK" << endl;
    return true;
    }



bool test_8bit_private_lookup () {

    bool success = true;

    // Scalar tests
   /* success = test_8bit_single_index_lookup({1, 2}, {0});
    success &= test_8bit_single_index_lookup({2, 3}, 0);
    success &= test_8bit_single_index_lookup({2, 3}, 1);
    success &= test_8bit_single_index_lookup({3, 4, 5}, 1);
    success &= test_8bit_single_index_lookup({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5);
    //success &= test_8bit_single_index_lookup({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 8);*/
    success &= test_8bit_multiple_index_lookup({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {3, 5, 6, 9});
    // ...

    return success;
}

/*bool test_32bit_single_index_lookup (std::vector<uint32_t> array, size_t index) {

    const size_t array_size = array.size();

    cout << "Testing 32-bit private lookup with index " << index<< " on a vector of " << array_size << " values ... ";

    // Declare three computing parties
    computing_party_state<shared_uint32_t, uint32_t> party1, party2, party3;

    // Share the secret vector
    party1.v.resize (array_size);
    party2.v.resize (array_size);
    party3.v.resize (array_size);
    if (!share (array, party1.v, party2.v, party3.v)) {
        cout << "FAILED! (Secret sharing of vector failed.)" << endl;
        return false;
    }

    // Share the index
    if (!share (element_n((uint32_t)(index + 1)), party1.j, party2.j, party3.j)) {
        cout << "FAILED! (Secret sharing of index failed.)" << endl;
        return false;
    }

    // Run the lookup
    if (!lookup (party1, party2, party3)) {
        cout << "FAILED! (Lookup protocol failed.)" << endl;
        return false;
    }

    // Reconstruct the result element
    uint32_t element = 0;
    if (!reconstruct (party1.w, party2.w, party3.w, element)) {
        cout << "FAILED! (Result reconstruction failed.)" << endl;
        return false;
    }

    // Check correctness of result
    if (element != array[index]) {
        cout << "FAILED! (Lookup result wrong: " << (uint32_t)element << ", expected " << (uint32_t)array[index] << ".)" << endl;
        return false;
    }

    cout << "OK" << endl;
    return true;
    }*/

bool test_32bit_multiple_index_lookup (std::vector<uint32_t> array, std::vector<uint32_t> index) {

    const size_t array_size = array.size();
    const size_t index_size = index.size();


    cout << "Testing 32-bit private lookup with " << index_size << " indices on a vector of " << array_size << " values ... ";

    // Declare three computing parties
    computing_party_state<shared_uint32_t, uint32_t> party1, party2, party3;

    // Share the secret vector
    party1.v.resize (array_size);
    party2.v.resize (array_size);
    party3.v.resize (array_size);
    if (!share (array, party1.v, party2.v, party3.v)) {
        cout << "FAILED! (Secret sharing of vector failed.)" << endl;
        return false;
    }

    // Share the index
    party1.j.resize(index_size);
    party2.j.resize(index_size);
    party3.j.resize(index_size);
    std::vector<uint32_t> index2;
    index2.resize(index_size);
    for (uint32_t i = 0; i < index_size; i++) {
        index2[i] = index[i] + 1;
    }
    if (!share (element_nvector(index2), party1.j, party2.j, party3.j)) {
        cout << "FAILED! (Secret sharing of index failed.)" << endl;
        return false;
    }
    // Run the lookup
    if (!lookup (party1, party2, party3)) {
        cout << "FAILED! (Lookup protocol failed.)" << endl;
        return false;
    }

    // Reconstruct the result element
    //uint8_t element = 0;
    std::vector<uint32_t> element;
    element.resize(party1.w.size());
    if (!reconstruct (party1.w, party2.w, party3.w, element)) {
        cout << "FAILED! (Result reconstruction failed.)" << endl;
        return false;
    }

    // Check correctness of result
    for (uint32_t i = 0; i < index_size; i++) {
        if (element[i] != array[index[i]]) {
            cout << "FAILED! (Lookup result wrong: " << (uint32_t)element[i] << ", expected " << (uint32_t)array[index[i]] << ".)" << endl;
            return false;
        }
    }
    cout << "OK" << endl;
    return true;
    }

bool test_32bit_private_lookup () {

    bool success = true;

    // Scalar tests
   /* success = test_32bit_single_index_lookup({1, 2}, 0);
    success &= test_32bit_single_index_lookup({2, 3}, 0);
    success &= test_32bit_single_index_lookup({2, 3}, 1);
    success &= test_32bit_single_index_lookup({3, 4, 5}, 1);
    success &= test_32bit_single_index_lookup({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5);
    success &= test_32bit_single_index_lookup({4123, 2, 51233, 4, 5, 231, 7, 8, 12, 10, 423, 12, 553, 1224, 12325, 12136, 13317, 18, 1319, 220}, 8);*/
    success &= test_32bit_multiple_index_lookup({1, 2, 5232, 2332, 5, 6, 7, 8, 9, 10}, {3, 5, 6, 9});
    // ...

    return success;
}


