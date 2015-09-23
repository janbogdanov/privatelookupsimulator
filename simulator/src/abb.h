#ifndef ABB
#define ABB
#include <iostream>
#include "secshare.h"
#include "profiler.h"


template<typename private_type>
bool abb_share (const private_type& s, private_type& share1, private_type& share2, private_type& share3) {
    begin_protocol();
    share (s, share1, share2, share3); //
    end_protocol();
    return true;
}

template<typename private_type>
bool abb_reconstruct (const private_type& share1, const private_type& share2, const private_type& share3, private_type& s) {
    begin_protocol();
    reconstruct (share1, share2, share3, s); //
    end_protocol();
    return true;
}

template<typename private_type>
bool abb_reconstruct_vec (const std::vector<private_type>& share1, const std::vector<private_type>& share2, const std::vector<private_type>& share3, std::vector<private_type>& s) {
    begin_protocol();
    s.resize(share1.size());
    std::vector<private_type> interm;
    for (uint32_t i = 0; i < share1.size(); i++) {
        reconstruct (share1[i], share2[i], share3[i], s[i]); //
    }
    end_protocol();
    return true;
}

template<typename private_type, typename public_type>
bool abb_add (const private_type& a1, const private_type& a2, const private_type& a3,
              const private_type& b1, const private_type& b2, const private_type& b3,
              private_type& c1, private_type& c2, private_type& c3) {
    c1 = gf2_add (a1, b1);
    c2 = gf2_add (a2, b2);
    c3 = gf2_add (a3, b3);

    return true;
}

template<typename private_type, typename public_type>
bool abb_add_vec (const std::vector<private_type>& a1, const std::vector<private_type>& a2, const std::vector<private_type>& a3,
              const std::vector<private_type>& b1, const std::vector<private_type>& b2, const std::vector<private_type>& b3,
              std::vector<private_type>& c1, std::vector<private_type>& c2, std::vector<private_type>& c3) {
    for (uint32_t i = 0; i < a1.size(); i++) {
        c1[i] = gf2_add (a1[i], b1[i]);
        c2[i] = gf2_add (a2[i], b2[i]);
        c3[i] = gf2_add (a3[i], b3[i]);
    }
    return true;
}

template<typename private_type, typename public_type>
bool abb_mult (const private_type& a1, const private_type& a2, const private_type& a3,
               const private_type& b1, const private_type& b2, const private_type& b3,
               private_type& c1, private_type& c2, private_type& c3) {

    begin_protocol();

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
    end_protocol();
    return true;
}

template<typename private_type, typename public_type>
bool abb_mult_vec (const std::vector<private_type>& a1, const std::vector<private_type>& a2, const std::vector<private_type>& a3,
                   const private_type& b1, const private_type& b2, const private_type b3,
                   std::vector<private_type>& c1, std::vector<private_type>& c2, std::vector<private_type>& c3) {

    begin_protocol();

    public_type b = 0;
    std::vector<public_type> a;
    std::vector<public_type> c;
    a.resize(a1.size());
    c.resize(a1.size());
    c1.resize(a1.size());
    c2.resize(a1.size());
    c3.resize(a1.size());

    for (uint32_t i = 0; i < a1.size(); i++) {
        if (!reconstruct (a1[i], a2[i], a3[i], a[i])) {
            std::cout << "Reconstruction of share 'a' failed!" << std::endl;
            return false;
        }

        if (!reconstruct (b1, b2, b3, b)) {
            std::cout << "Reconstruction of share 'b' failed!" << std::endl;
            return false;
        }

        c[i] = gf2_mul (a[i], b);

        if (!share (c[i], c1[i], c2[i], c3[i])) {
            std::cout << "Sharing failed!" << std::endl;
            return false;
        }
    }
    end_protocol();
    return true;
}



template<typename private_type, typename public_type>
bool abb_mult_pub (const private_type& a1, const private_type& a2, const private_type& a3,
                   const public_type& b1, const public_type& b2, const public_type& b3,
                   private_type& c1, private_type& c2, private_type& c3) {
    c1 = gf2_mul(a1, b1);
    c2 = gf2_mul(a2, b2);
    c3 = gf2_mul(a3, b3);

    return true;
}

template<typename private_type, typename public_type>
bool abb_mult_pub_final_calc (const private_type& a1, const private_type& a2, const private_type& a3,
                   const public_type& b, const public_type& k,
                   private_type& c1, private_type& c2, private_type& c3) {
    c1 = gf2_mul(a1, gf2_pwr(b, k));
    c2 = gf2_mul(a2, gf2_pwr(b, k));
    c3 = gf2_mul(a3, gf2_pwr(b, k));

    return true;
}

template<typename private_type, typename public_type>
bool abb_mult_pub_final_calc_vec (const private_type& a1, const private_type& a2, const private_type& a3,
                   const std::vector<public_type>& b, const public_type& k,
                   std::vector<private_type>& c1, std::vector<private_type>& c2, std::vector<private_type>& c3) {
    for (uint32_t i = 0; i < b.size(); i++) {
        c1[i] = gf2_mul(a1, gf2_pwr(b[i], k));
        c2[i] = gf2_mul(a2, gf2_pwr(b[i], k));
        c3[i] = gf2_mul(a3, gf2_pwr(b[i], k));
    }
    return true;
}
#endif // ABB

