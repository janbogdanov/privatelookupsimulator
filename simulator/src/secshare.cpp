#include "secshare.h"

// TODO Make these use gf2_random

bool share (uint8_t value, shared_uint8_t &s1, shared_uint8_t &s2, shared_uint8_t &s3) { 
    s1 = rand() % 255;
    //s1 = 0;
    s2 = rand() % 255;
    //s2 = 0;
    s3 = value ^ s1 ^ s2;
    return true;
}

bool share (const std::vector<uint8_t>& value, std::vector<shared_uint8_t> &s1, std::vector<shared_uint8_t> &s2, std::vector<shared_uint8_t> &s3) {
    for (std::vector<shared_uint8_t>::iterator it=s1.begin(); it != s1.end() ;++it)
    {
        *it = rand() % 255;
        //*it = 0;
    }
    for (std::vector<shared_uint8_t>::iterator it=s2.begin(); it != s2.end() ;++it)
    {
        *it = rand() % 255;
        //*it = 0;
    }
    uint32_t i = 0;
    for (i = 0; i <= value.size()-1; i++)
    {
        s3[i] = value[i] ^ s1[i] ^ s2[i];
    }
    return true;
}

bool share (uint32_t value, shared_uint32_t &s1, shared_uint32_t &s2, shared_uint32_t &s3) {
    s1 = rand() % 4294967295;
    s2 = rand() % 4294967295;
    s3 = value ^ s1 ^ s2;
    return true;
}

bool share (const std::vector<uint32_t>& value, std::vector<shared_uint32_t> &s1, std::vector<shared_uint32_t> &s2, std::vector<shared_uint32_t> &s3) {
    for (std::vector<shared_uint32_t>::iterator it = s1.begin(); it != s1.end() ;++it)
    {
        *it = rand() % 4294967295;
    }

    for (std::vector<shared_uint32_t>::iterator it = s2.begin(); it != s2.end() ;++it)
    {
        *it = rand() % 4294967295;
    }
        uint32_t i = 0;
    for (i = 0; i <= value.size()-1; i++)
    {
        s3[i] = value[i] ^ s1[i] ^ s2[i];
    }
    return true;
}

bool reconstruct (shared_uint8_t s1, shared_uint8_t s2, shared_uint8_t s3, uint8_t &value) {
    value = s1 ^ s2 ^ s3;
    return true;
}

bool reconstruct (const std::vector<shared_uint8_t> &s1, const std::vector<shared_uint8_t> &s2, const std::vector<shared_uint8_t> &s3, std::vector<uint8_t>& value) {
    uint32_t i = 0;
    value.resize(s1.size());
    for (i = 0; i < value.size(); i++)
    {
        value[i] = s1[i] ^ s2[i] ^ s3[i];
    }
    return true;
}

bool reconstruct (shared_uint32_t s1, shared_uint32_t s2, shared_uint32_t s3, uint32_t &value) {
    value = s1 ^ s2 ^ s3;
    return true;
}

bool reconstruct (const std::vector<shared_uint32_t> &s1, const std::vector<shared_uint32_t> &s2, const std::vector<shared_uint32_t> &s3, std::vector<uint32_t>& value) {
    uint32_t i = 0;
    for (i = 0; i < value.size(); i++)
    {
        value[i] = s1[i] ^ s2[i] ^ s3[i];
    }
    return true;
}

