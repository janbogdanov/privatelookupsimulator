#include <iostream>
#include <cstdlib>
#include "gf2_tests.h"
#include "secshare_tests.h"
#include "lookup_tests.h"

using namespace std;

int main(int argc, char *argv[]) {


    bool success = false;
    cout << "*** TESTING GF_2**8 ARITHMETIC ***" << endl;
    success = test_gf2to8_arithmetic ();
    if (success)
        cout << "*** GF_2**8 ARITHMETIC OK.***" << endl;
    else
        cout << "*** GF_2**8 ARITHMETIC FAILED!***" << endl;
    cout << endl;

    cout << "*** TESTING GF_2**32 ARITHMETIC ***" << endl;
    success = test_gf2to32_arithmetic ();
    if (success)
        cout << "*** GF_2**32 ARITHMETIC OK.***" << endl;
    else
        cout << "*** GF_2**32 ARITHMETIC FAILED!***" << endl;
    cout << endl;

    cout << "*** TESTING GF_2**8 SECRET SHARING***" << endl;
    success = test_8bit_secret_sharing ();
    if (success)
        cout << "*** GF_2**8 SECRET SHARING OK.***" << endl;
    else
        cout << "*** GF_2**8 SECRET SHARING FAILED!***" << endl;
    cout << endl;

    cout << "*** TESTING GF_2**32 SECRET SHARING***" << endl;
    success = test_32bit_secret_sharing ();
    if (success)
        cout << "*** GF_2**32 SECRET SHARING OK.***" << endl;
    else
        cout << "*** GF_2**32 SECRET SHARING FAILED!***" << endl;
    cout << endl;

    /*
    cout << "*** TESTING GF_2**8 PRIVATE LOOKUP***" << endl;
    success = test_gf2to8_private_lookup ();
    if (success)
        cout << "*** GF_2**8 PRIVATE LOOKUP OK.***" << endl;
    else
        cout << "*** GF_2**8 PRIVATE LOOKUP FAILED!***" << endl;
    cout << endl;

    cout << "*** TESTING GF_2**32 PRIVATE LOOKUP***" << endl;
    success = test_gf2to32_private_lookup ();
    if (success)
        cout << "*** GF_2**32 PRIVATE LOOKUP OK.***" << endl;
    else
        cout << "*** GF_2**32 PRIVATE LOOKUP FAILED!***" << endl;
    */

    return EXIT_SUCCESS;
}
