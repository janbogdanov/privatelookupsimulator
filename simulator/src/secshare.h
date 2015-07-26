#ifndef SECSHARE_H
#define SECSHARE_H

#include "gf2_ops.h"
#include <vector>

// Declare secret types
typedef gf2to8_t shared_uint8_t;
typedef gf2to32_t shared_uint32_t;

// 8-bit variants
bool share (uint8_t value, shared_uint8_t &s1, shared_uint8_t &s2, shared_uint8_t &s3);
bool share (const std::vector<uint8_t>& value, std::vector<shared_uint8_t> &s1, std::vector<shared_uint8_t> &s2, std::vector<shared_uint8_t> &s3);
bool reconstruct (shared_uint8_t s1, shared_uint8_t s2, shared_uint8_t s3, uint8_t &value);
bool reconstruct (const std::vector<shared_uint8_t> &s1, const std::vector<shared_uint8_t> &s2, const std::vector<shared_uint8_t> &s3, std::vector<uint8_t>& value);

// 32-bit variants
bool share (uint32_t value, shared_uint32_t &s1, shared_uint32_t &s2, shared_uint32_t &s3);
bool share (const std::vector<uint32_t>& value, std::vector<shared_uint32_t> &s1, std::vector<shared_uint32_t> &s2, std::vector<shared_uint32_t> &s3);
bool reconstruct (shared_uint32_t s1, shared_uint32_t s2, shared_uint32_t s3, uint32_t &value);
bool reconstruct (const std::vector<shared_uint32_t> &s1, const std::vector<shared_uint32_t> &s2, const std::vector<shared_uint32_t> &s3, std::vector<uint32_t>& value);

#endif // SECSHARE_H

