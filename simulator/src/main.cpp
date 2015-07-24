#include <iostream>
#include <cstdlib>

#include "gf2_ops.h"
#include "secshare.h"
#include "lookup.h"


using namespace std;

bool test_gf2to8_arithmetic () {

    return false;
}

bool test_gf2to32_arithmetic () {

    return false;
}


bool test_gf2to8_secret_sharing () {

    return false;
}

bool test_gf2to32_secret_sharing () {

    return false;
}

bool test_gf2to8_private_lookup () {

    return false;
}

bool test_gf2to32_private_lookup () {

    return false;
}

int main(int argc, char *argv[]) {


    bool success = false;
    cout << "*** TESTING GF_2**8 ARITHMETIC ***" << endl;
    success = test_gf2to8_arithmetic ();
    if (success)
        cout << "*** GF_2**8 ARITHMETIC OK.***" << endl;
    else
        cout << "*** GF_2**8 ARITHMETIC FAILED!***" << endl;

    cout << "*** TESTING GF_2**32 ARITHMETIC ***" << endl;
    success = test_gf2to32_arithmetic ();
    if (success)
        cout << "*** GF_2**32 ARITHMETIC OK.***" << endl;
    else
        cout << "*** GF_2**32 ARITHMETIC FAILED!***" << endl;

    cout << "*** TESTING GF_2**8 SECRET SHARING***" << endl;
    success = test_gf2to8_secret_sharing ();
    if (success)
        cout << "*** GF_2**8 SECRET SHARING OK.***" << endl;
    else
        cout << "*** GF_2**8 SECRET SHARING FAILED!***" << endl;

    cout << "*** TESTING GF_2**32 SECRET SHARING***" << endl;
    success = test_gf2to32_secret_sharing ();
    if (success)
        cout << "*** GF_2**32 SECRET SHARING OK.***" << endl;
    else
        cout << "*** GF_2**32 SECRET SHARING FAILED!***" << endl;

    cout << "*** TESTING GF_2**8 PRIVATE LOOKUP***" << endl;
    success = test_gf2to8_private_lookup ();
    if (success)
        cout << "*** GF_2**8 PRIVATE LOOKUP OK.***" << endl;
    else
        cout << "*** GF_2**8 PRIVATE LOOKUP FAILED!***" << endl;

    cout << "*** TESTING GF_2**32 PRIVATE LOOKUP***" << endl;
    success = test_gf2to32_private_lookup ();
    if (success)
        cout << "*** GF_2**32 PRIVATE LOOKUP OK.***" << endl;
    else
        cout << "*** GF_2**32 PRIVATE LOOKUP FAILED!***" << endl;


    return EXIT_SUCCESS;
}
