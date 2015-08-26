#ifndef LOOKUP_H
#define LOOKUP_H

#include <vector>
#include <iostream>
#include "secshare.h"
#include "abb.h"


#define DEBUGPRINT_8(VAR)\
    {gf2to8_t v = 0;\
    abb_reconstruct (party1.VAR, party2.VAR, party3.VAR, v);\
    std::cout << #VAR << " " << (uint32_t)v << std::endl;}

template<typename private_type, typename public_type>
struct computing_party_state{
    // The secret vector
    std::vector<private_type> v;
    // The secret index
    private_type j = 0;

    // Random r and inverse generation
    private_type a = 0;
    private_type a1 = 0;
    private_type a2 = 0;
    private_type a3 = 0;
    private_type ap = 0;
    private_type b = 0;
    private_type b1 = 0;
    private_type b2 = 0;
    private_type b3 = 0;
    private_type bp = 0;
    private_type c1 = 0;
    private_type c2 = 0;
    private_type c3 = 0;
    private_type r = 0;
    private_type r_inv = 0;

    //calculate power of r
    std::vector<private_type> r_powers;

    // The result
    private_type w = 0;

};

template<typename private_type, typename public_type>
bool generate_r_with_inverse (computing_party_state<private_type, public_type>& party1,
                              computing_party_state<private_type, public_type>& party2,
                              computing_party_state<private_type, public_type>& party3)
{

    public_type c = 0;
    do {
        // Locally generate a
        gf2_random (party1.a);
        abb_share<private_type>(party1.a, party1.a1, party2.a1, party3.a1);
        gf2_random (party2.a);
        abb_share<private_type>(party2.a, party1.a2, party2.a2, party3.a2);
        gf2_random (party3.a);
        abb_share<private_type>(party3.a, party1.a3, party2.a3, party3.a3);
        party1.ap = gf2_add(party1.a1, gf2_add (party1.a2, party1.a3));
        party2.ap = gf2_add(party2.a1, gf2_add (party2.a2, party2.a3));
        party3.ap = gf2_add(party3.a1, gf2_add (party3.a2, party3.a3));

        //Locally generate b
        gf2_random (party1.b);
        abb_share<private_type>(party1.b, party1.b1, party2.b1, party3.b1);
        gf2_random (party2.b);
        abb_share<private_type>(party2.b, party1.b2, party2.b2, party3.b2);
        gf2_random (party3.b);
        abb_share<private_type>(party3.b, party1.b3, party2.b3, party3.b3);
        party1.bp = gf2_add(party1.b1, gf2_add (party1.b2, party1.b3));
        party2.bp = gf2_add(party2.b1, gf2_add (party2.b2, party2.b3));
        party3.bp = gf2_add(party3.b1, gf2_add (party3.b2, party3.b3));

        if (!abb_mult<private_type, public_type> (party1.ap, party2.ap, party3.ap,
                  party1.bp, party2.bp, party3.bp,
                  party1.c1, party2.c2, party3.c3)) {
            std::cout << "abb_mult failed!" << std::endl;
            return false;
        }

        if (!abb_reconstruct (party1.c1, party2.c2, party3.c3, c)) {
            std::cout << "abb_reconstruct failed!" << std::endl;
            return false;
        }

    } while (c == 0);

    public_type c_inv = gf2_inv(c);
    party1.r = party1.ap;
    party2.r = party2.ap;
    party3.r = party3.ap;

    party1.r_inv = gf2_mul(party1.bp, c_inv);
    party2.r_inv = gf2_mul(party2.bp, c_inv);
    party3.r_inv = gf2_mul(party3.bp, c_inv);

    return true;
}

template<typename private_type, typename public_type>
bool calc_powers_of_r (
                  computing_party_state<private_type, public_type>& party1,
                  computing_party_state<private_type, public_type>& party2,
                  computing_party_state<private_type, public_type>& party3)
{
    uint32_t k = 0;
/*    for (k = 2; (k < v.size()-1) ;k++) {
        r_values1[k-2] = gf2_pwr(party1, k-1);
        r_values2[k-2] = gf2_pwr(party2, k-1);
        r_values3[k-2] = gf2_pwr(party3, k-1);
        return true;
    }*/
}

template<typename private_type, typename public_type>
bool lookup (computing_party_state<private_type, public_type>& party1,
             computing_party_state<private_type, public_type>& party2,
             computing_party_state<private_type, public_type>& party3) {

    if (!generate_r_with_inverse (party1, party2, party3)) {
        std::cout << "generate_r_with_inverse failed!" << std::endl;
        return false;
    }

    std::cout << std::endl;
    DEBUGPRINT_8(r);
    DEBUGPRINT_8(r_inv);

    if (!calc_powers_of_r (party1, party2, party3)) {
        std::cout << "calc_powers_of_r failed!" << std::endl;
        return false;
    }
    uint32_t i = 0;
    for (i = 0; i < party1.r_powers.size(); i++) {
        std::cout << std::endl;
        DEBUGPRINT_8(r_powers[i]);

    }

    return true;
}



#endif // LOOKUP_H



