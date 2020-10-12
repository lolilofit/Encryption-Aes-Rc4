//
// Created by User on 05.10.2020.
//

#include "AesUtils.h"

byte_t mult_by_2(byte_t x) { return (x < 128) ? x << 1 : (x << 1 & 0xff) ^ 0x1b; }

byte_t mult_by_8(byte_t x) { return mult_by_2(mult_by_2(mult_by_2(x))); }

byte_t vector_mult(const std::array<byte_t, 4>& v1, std::array<byte_t, 4>&& v2) {
    std::transform(begin(v1), end(v1), begin(v2), begin(v2),
                   [](byte_t x, byte_t y) { return mapper.at(y)(x); });
    return std::accumulate(begin(v2), end(v2), byte_t(0), std::bit_xor<byte_t>());
}

