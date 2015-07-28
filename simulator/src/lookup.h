#ifndef LOOKUP_H
#define LOOKUP_H

#include <vector>

template<typename private_type, typename public_type>
struct computing_party_state{
    // The secret vector
    std::vector<private_type> v;
    // The secret index
    private_type j = 0;

    // TODO intermediate values here

    // The result
    private_type w = 0;

};

template<typename private_type, typename public_type>
bool lookup (computing_party_state<private_type, public_type>& party1,
             computing_party_state<private_type, public_type>& party2,
             computing_party_state<private_type, public_type>& party3) {

    // TODO Implement the algorithm here

    return false;
}

#endif // LOOKUP_H

