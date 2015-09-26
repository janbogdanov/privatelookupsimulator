#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include "lookup_tests.h"
#include "lookup.h"
#include "secshare.h"

using namespace std;

bool test_8bit_multiple_index_lookup (std::vector<uint8_t> array, std::vector<uint8_t> index) {

    const size_t array_size = array.size();
    const size_t index_size = index.size();

    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "\nTesting 8-bit private lookup with ";
    time_log << index_size;
    time_log << " indices on a vector of ";
    time_log << array_size;
    time_log << " values ... \n";
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
    std::vector<uint8_t> random_array;
    std::vector<uint8_t> random_index;
    // Scalar tests
    for (uint32_t i = 2; i < 257;) {
        random_array.clear();
        random_array.resize(i);
        random_index.clear();
        random_index.resize(i/2);
        i = i << 1;
        for (uint32_t q = 0; q < random_array.size(); q++) {
            random_array[q] = rand() % 256;
        }
        for (uint32_t q = 0; q < random_index.size(); q++) {
            random_index[q] = rand() % random_index.size();
        }
        success &= test_8bit_multiple_index_lookup(random_array, random_index);
    }

    return success;
}

bool test_32bit_multiple_index_lookup (std::vector<uint32_t> array, std::vector<uint32_t> index) {

    const size_t array_size = array.size();
    const size_t index_size = index.size();

    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "\nTesting 32-bit private lookup with ";
    time_log << index_size;
    time_log << " indices on a vector of ";
    time_log << array_size;
    time_log << " values ... \n";
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
    std::vector<uint32_t> random_array;
    std::vector<uint32_t> random_index;
    // Scalar tests
    for (uint32_t i = 2; i < 1025;) {
        random_array.clear();
        random_array.resize(i);
        random_index.clear();
        random_index.resize(i/2);
        i = i << 1;
        for (uint32_t q = 0; q < random_array.size(); q++) {
            random_array[q] = rand() % 4294967296;
        }
        for (uint32_t q = 0; q < random_index.size(); q++) {
            random_index[q] = rand() % random_index.size();
        }
        success &= test_32bit_multiple_index_lookup(random_array, random_index);
    }

    return success;
}


