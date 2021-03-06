#ifndef LOOKUP_H
#define LOOKUP_H

#include <vector>
#include <iostream>
#include <fstream>
#include "secshare.h"
#include "profiler.h"
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
    //private_type j = 0;
    std::vector<private_type> j;

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

    //calculate lagrange coefficients
    std::vector<public_type> temporary;
    std::vector<public_type> coefficients;
    std::vector<public_type> basicpoly;

    //calculate vector-only phase
    //private_type c_interm = 0;
    std::vector<private_type> ck;
    std::vector<private_type> yk;

    //calculate online phase
    /*private_type z_private = 0;// vektoriks
    public_type z = 0;
    public_type z_interm = 0;*/

    std::vector<private_type> z_private;
    std::vector<public_type> z;
    std::vector<public_type> z_interm;

    // The result
    //private_type w = 0;
    std::vector<private_type> w;

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
    party1.r_powers.resize(party1.v.size() + 1);
    party2.r_powers.resize(party2.v.size() + 1);
    party3.r_powers.resize(party3.v.size() + 1);
    party1.r_powers[0] = 1;
    party2.r_powers[0] = 0;
    party3.r_powers[0] = 0;
    party1.r_powers[1] = party1.r;
    party2.r_powers[1] = party2.r;
    party3.r_powers[1] = party3.r;
    for (k = 2; k <= party1.v.size(); k++) {
        if(!abb_mult<private_type, public_type> (party1.r_powers[k-1], party2.r_powers[k-1], party3.r_powers[k-1],
                                                           party1.r, party2.r, party3.r,
                                                           party1.r_powers[k], party2.r_powers[k], party3.r_powers[k])) {
            std::cout << "abb_mult(r) failed!" << std::endl;
            return false;
        }
    }
    return true;
}


template<typename private_type, typename public_type>
bool calc_lagrange_basepoly     (computing_party_state<private_type, public_type>& party1,
                                 computing_party_state<private_type, public_type>& party2,
                                 computing_party_state<private_type, public_type>& party3) {
    uint32_t i = 0;
    size_t onepoint = 0;
    uint32_t vectorsize = party1.v.size();
    party1.temporary.resize(vectorsize);
    party2.temporary.resize(vectorsize);
    party3.temporary.resize(vectorsize);
    party1.coefficients.resize (vectorsize*vectorsize, 0);
    party2.coefficients.resize (vectorsize*vectorsize, 0);
    party3.coefficients.resize (vectorsize*vectorsize, 0);
    party1.basicpoly.resize(vectorsize);
    party2.basicpoly.resize(vectorsize);
    party3.basicpoly.resize(vectorsize);
    std::vector<public_type> indices;
    indices.resize(party1.v.size());
    for (i = 0; i < vectorsize; i++) {
        uint32_t field_i = i + 1;           // uint8_t läks uint32_t'ks 24.09.2015 14.42
        indices[i] = element_n(field_i);
    }
    for (onepoint = 0; onepoint < vectorsize; onepoint++) {
        party1.basicpoly.clear();
        party2.basicpoly.clear();
        party3.basicpoly.clear();
        party1.basicpoly.resize(vectorsize);
        party2.basicpoly.resize(vectorsize);
        party3.basicpoly.resize(vectorsize);
        party1.basicpoly[0] = 1;
        party2.basicpoly[0] = 1;
        party3.basicpoly[0] = 1;
        for (size_t k = 0; k < vectorsize; k++){
            if (onepoint != k) {
                for(i = 0; i < vectorsize; i++) {
                    party1.temporary[i] = party1.basicpoly[i];
                    party2.temporary[i] = party2.basicpoly[i];
                    party3.temporary[i] = party3.basicpoly[i];
                }
                private_type invdiff = gf2_inv(gf2_add(indices[onepoint], indices[k]));
                private_type freeterm = gf2_mul(indices[k], invdiff);

                for (i = 0; i < vectorsize; i++) {
                    party1.basicpoly[i] = gf2_mul(party1.temporary[i], freeterm);
                    party2.basicpoly[i] = gf2_mul(party2.temporary[i], freeterm);
                    party3.basicpoly[i] = gf2_mul(party3.temporary[i], freeterm);
                    if (i > 0) {
                        party1.basicpoly[i] = gf2_add(party1.basicpoly[i], gf2_mul(party1.temporary[i-1], invdiff));
                        party2.basicpoly[i] = gf2_add(party2.basicpoly[i], gf2_mul(party2.temporary[i-1], invdiff));
                        party3.basicpoly[i] = gf2_add(party3.basicpoly[i], gf2_mul(party3.temporary[i-1], invdiff));
                    }
                }
            }
        }
        for (i = 0; i < vectorsize; i++) {
            party1.coefficients[i * vectorsize + onepoint] = party1.basicpoly[i];
            party2.coefficients[i * vectorsize + onepoint] = party2.basicpoly[i];
            party3.coefficients[i * vectorsize + onepoint] = party3.basicpoly[i];
        }
    }
    return true;
}

template<typename private_type, typename public_type>
bool calculate_c (computing_party_state<private_type, public_type>& party1,
                  computing_party_state<private_type, public_type>& party2,
                  computing_party_state<private_type, public_type>& party3) {

    private_type c_interm1 = 0;
    private_type c_interm2 = 0;
    private_type c_interm3 = 0;
    uint32_t i = 0;
    uint32_t k = 0;
    uint32_t vectorsize = party1.v.size();
    party1.ck.resize(vectorsize);
    party2.ck.resize(vectorsize);
    party3.ck.resize(vectorsize);
    // veel üks 'for'
    for (k = 0; k < vectorsize; k++) {
        for (i = 0; i < vectorsize; i++) {
            if (!abb_mult_pub<private_type, public_type> (party1.v[i], party2.v[i], party3.v[i],
                                                          party1.coefficients[k * vectorsize + i], party2.coefficients[k * vectorsize + i], party3.coefficients[k * vectorsize + i],
                                                          c_interm1, c_interm2, c_interm3)) {
                std::cout << "abb_mult_pub failed!(calculate_c)" << std::endl;
                return false;
            }
            if (!abb_add<private_type, public_type> (party1.ck[k], party2.ck[k], party3.ck[k],
                                                     c_interm1, c_interm2, c_interm3,
                                                     party1.ck[k], party2.ck[k], party3.ck[k])) {
                std::cout << "abb_add failed!(calculate_c)" << std::endl;
                return false;
            }
        }
    }
    return true;
}

template<typename private_type, typename public_type>
bool calculate_y (computing_party_state<private_type, public_type>& party1,
                  computing_party_state<private_type, public_type>& party2,
                  computing_party_state<private_type, public_type>& party3) {

    uint32_t k = 0;
    uint32_t vectorsize = party1.v.size();
    party1.yk.resize(vectorsize);
    party2.yk.resize(vectorsize);
    party3.yk.resize(vectorsize);
    for (k = 0; k < vectorsize; k++) {
        if(!abb_mult<private_type, public_type> (party1.ck[k], party2.ck[k], party3.ck[k],
                                                 party1.r_powers[k], party2.r_powers[k], party3.r_powers[k],
                                                 party1.yk[k], party2.yk[k], party3.yk[k])) {
            std::cout << "abb_mult failed!(calculate_y)" << std::endl;
            return false;
        }
    }
    return true;
}

template<typename private_type, typename public_type>
bool calculate_z (computing_party_state<private_type, public_type>& party1,
                  computing_party_state<private_type, public_type>& party2,
                  computing_party_state<private_type, public_type>& party3) {

   // abb_mult_vec siia! ette anda j massiivi; deklareerin massiivi, kus kopeerin r_inv nii palju kui vaja
    if (!abb_mult_vec<private_type, public_type> (party1.j, party2.j, party3.j,     // ztidest massiiv, j ka massiiv
              party1.r_inv, party2.r_inv, party3.r_inv,
              party1.z_private, party2.z_private, party3.z_private)) {
        std::cout << "abb_mult failed!(calculate_z)" << std::endl;
        return false;
    }

    /*if (!abb_mult<private_type, public_type> (party1.j, party2.j, party3.j,     // ztidest massiiv, j ka massiiv
              party1.r_inv, party2.r_inv, party3.r_inv,
              party1.z_private, party2.z_private, party3.z_private)) {
        std::cout << "abb_mult failed!(calculate_z)" << std::endl;
        return false;
    }*/

    //public_type z_interm = 0;
    std::vector<public_type> z_interm;

     // abb_reconstruct_vec
    if (!abb_reconstruct_vec<private_type> (party1.z_private, party2.z_private, party3.z_private, z_interm)) {
        std::cout << "reconstruction failed!(z)" << std::endl;
        return false;
    }
    party1.z_interm = z_interm;
    party2.z_interm = z_interm;
    party3.z_interm = z_interm;

    return true;
}

template<typename private_type, typename public_type>
bool calculate_w (computing_party_state<private_type, public_type>& party1,
                  computing_party_state<private_type, public_type>& party2,
                  computing_party_state<private_type, public_type>& party3) {
    uint32_t k = 0;
    uint32_t vectorsize = party1.v.size();
    /*public_type w_interm1 = 0;
    public_type w_interm2 = 0;
    public_type w_interm3 = 0;*/
    std::vector<private_type> w_interm1;
    std::vector<private_type> w_interm2;
    std::vector<private_type> w_interm3;
    w_interm1.resize(vectorsize);
    w_interm2.resize(vectorsize);
    w_interm3.resize(vectorsize);
    party1.w.resize(vectorsize);
    party2.w.resize(vectorsize);
    party3.w.resize(vectorsize);
    for (k = 0; k < vectorsize; k++) {
        // abb mult pub finalist calc vec versioon? kutsutakse kõigi zttide peal; w_intermid on ka massiivid
        /*if (!abb_mult_pub_final_calc<private_type, public_type> (party1.yk[k], party2.yk[k], party3.yk[k],
                                                                 party1.z_interm, k,
                                                                 w_interm1, w_interm2, w_interm3)) {
            std::cout << "abb_mult_pub_final_calc failed!(w)" << std::endl;
            return false;*/
        if (!abb_mult_pub_final_calc_vec<private_type, public_type> (party1.yk[k], party2.yk[k], party3.yk[k],
                                                                         party1.z_interm, k,
                                                                         w_interm1, w_interm2, w_interm3)) {
                    std::cout << "abb_mult_pub_final_calc failed!(w)" << std::endl;
                    return false;
        }
        // vec versioon
        if (!abb_add_vec<private_type, public_type> (party1.w, party2.w, party3.w,
                                                 w_interm1, w_interm2, w_interm3,
                                                 party1.w, party2.w, party3.w)) {
            std::cout << "abb_add failed!(w)" << std::endl;
            return false;
        }
    }
    return true;
}

template<typename private_type, typename public_type>
bool lookup (computing_party_state<private_type, public_type>& party1,
             computing_party_state<private_type, public_type>& party2,
             computing_party_state<private_type, public_type>& party3) {

    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "--- Offline phase start ---\n";
    time_log.flush();

    begin_profile();

    time_log << "generate_r_with_inverse start\n";
    time_log.flush();
    if (!generate_r_with_inverse (party1, party2, party3)) {
        std::cout << "generate_r_with_inverse failed!" << std::endl;
        return false;
    }
    time_log << "generate_r_with_inverse end\n";
    time_log.flush();
    /*std::cout << std::endl;
    DEBUGPRINT_8(r);
    DEBUGPRINT_8(r_inv);*/

    time_log << "calc_powers_of_r start\n";
    time_log.flush();
    if (!calc_powers_of_r (party1, party2, party3)) {
        std::cout << "calc_powers_of_r failed!" << std::endl;
        return false;
    }
    time_log << "calc_powers_of_r end\n";
    time_log.flush();
    /*uint32_t i = 0;
    for (i = 0; i < party1.r_powers.size(); i++) {
        DEBUGPRINT_8(r_powers[i]);
    }*/
    time_log << "calc_lagrange_basepoly start\n";
    time_log.flush();
    if (!calc_lagrange_basepoly (party1, party2, party3)) {
        std::cout << "calc_lagrange_basepoly failed!" << std::endl;
        return false;
    }
    time_log << "calc_lagrange_basepoly end\n";
    time_log.flush();
    /*for (i = 0; i < party1.coefficients.size(); i++) {
        std::cout << "coefficients[" << i << "]" << (uint32_t)party1.coefficients[i] << std::endl;
    }*/

    time_log << "--- Offline phase end ---\n";
    time_log.flush();
    end_profile();
    time_log << "\n--- Vector-only phase start ---\n";
    time_log.flush();
    time_log << "calculate_c start\n";
    time_log.flush();
    begin_profile();
    if (!calculate_c (party1, party2, party3)) {
        std::cout << "calc_c failed!" << std::endl;
        return false;
    }
    time_log << "calculate_c end\n";
    time_log.flush();
    /*for (i = 0; i < party1.ck.size(); i++) {
        DEBUGPRINT_8(ck[i]);
    }*/
    time_log << "calculate_y start\n";
    time_log.flush();
    if (!calculate_y (party1, party2, party3)) {
        std::cout << "calc_w failed!" << std::endl;
        return false;
    }
    time_log << "calculate_y end\n";
    time_log.flush();
    /*for (i = 0; i < party1.yk.size(); i++) {
        DEBUGPRINT_8(yk[i]);
    }*/

    time_log << "--- Vector-only phase end ---\n";
    time_log.flush();
    end_profile();
    time_log << "\n--- Online phase start ---\n";
    time_log.flush();
    time_log << "calculate_z start\n";
    time_log.flush();
    begin_profile();

    if (!calculate_z (party1, party2, party3)) {
        std::cout << "calc_z failed!" << std::endl;
        return false;
    }
    time_log << "calculate_z end\n";
    time_log.flush();
    //std::cout << "z_interm " << (uint32_t)party1.z_interm << std::endl;
    time_log << "calculate_w start\n";
    time_log.flush();
    if (!calculate_w (party1, party2, party3)) {
        std::cout << "calc_w failed!" << std::endl;
        return false;
    }
    time_log << "calculate_w end\n";
    time_log.flush();
    time_log << "--- Online phase end ---\n";
    time_log.flush();
    end_profile();
    time_log << "\n\n";
    time_log.flush();
    //DEBUGPRINT_8(w);
    return true;
}



#endif // LOOKUP_H



