#ifndef ABB
#define ABB
#include <iostream>
#include "secshare.h"

template<typename private_type>
bool abb_share (const private_type& s, private_type& share1, private_type& share2, private_type& share3) {
    return share (s, share1, share2, share3);
}
template<typename private_type>
bool abb_reconstruct (const private_type& share1, const private_type& share2, const private_type& share3, private_type& s) {
    return reconstruct (share1, share2, share3, s);
}


template<typename private_type, typename public_type>
bool abb_add (const private_type& a1, const private_type a2, const private_type a3,
              const private_type& b1, const private_type b2, const private_type b3,
              private_type& c1, private_type& c2, private_type& c3) {
    c1 = gf2_add (a1, b1);
    c2 = gf2_add (a2, b2);
    c3 = gf2_add (a3, b3);

    return true;
}

template<typename private_type, typename public_type>
bool abb_mult (const private_type& a1, const private_type a2, const private_type a3,
               const private_type& b1, const private_type b2, const private_type b3,
               private_type& c1, private_type& c2, private_type& c3) {

    public_type a = 0, b = 0, c = 0;

    if (!reconstruct (a1, a2, a3, a)) {
        std::cout << "Reconstruction of share 'a' failed!" << std::endl;
        return false;
    }

    if (!reconstruct (b1, b2, b3, b)) {
        std::cout << "Reconstruction of share 'b' failed!" << std::endl;
        return false;
    }

    c = gf2_mul (a, b);

    if (!share (c, c1, c2, c3)) {
        std::cout << "Sharing failed!" << std::endl;
        return false;
    }
    return true;
}

template<typename private_type, typename public_type>
bool abb_mult_pub (const private_type& a1, const private_type a2, const private_type a3,
                   const public_type& b,
                   private_type& c1, private_type& c2, private_type& c3) {
    c1 = gf2_mul(a1, b);
    c2 = gf2_mul(a2, b);
    c3 = gf2_mul(a3, b);

    return true;
}

#endif // ABB

