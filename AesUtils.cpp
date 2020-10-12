//
// Created by User on 05.10.2020.
//

#include "AesUtils.h"

unsigned char mult_with_shift(unsigned char x) { return (x < 128) ? x << 1 : (x << 1 & 0xff) ^ 0x1b; }

unsigned char mult_req(unsigned char x) { return mult_with_shift(mult_with_shift(mult_with_shift(x))); }

unsigned char vector_mult(const std::array<unsigned char, 4>& v1, std::array<unsigned char, 4>&& v2) {
    std::transform(begin(v1), end(v1), begin(v2), begin(v2),
                   [](unsigned char x, unsigned char y) { return ((const std::unordered_map<unsigned char, std::function<unsigned char(
                           unsigned char)>>) {
                           {0x1, [](unsigned char x) { return x; }},
                           {0x2, [](unsigned char x) { return (x < 128) ? x << 1 : (x << 1 & 0xff) ^ 0x1b; }},
                           {0x3, [](unsigned char x) { return mult_with_shift(x) ^ x; }},
                           {0x9, [](unsigned char x) { return mult_req(x) ^ x; }},
                           {0xb, [](unsigned char x) { return mult_req(x) ^ mult_with_shift(x) ^ x; }},
                           {0xd, [](unsigned char x) { return mult_req(x) ^ mult_with_shift(mult_with_shift(x)) ^ x; }},
                           {0xe, [](unsigned char x) {
                               return mult_req(x) ^ mult_with_shift(mult_with_shift(x)) ^ mult_with_shift(x);
                           }},
                   }).at(y)(x); });
    return std::accumulate(begin(v2), end(v2), (unsigned char)(0), std::bit_xor<unsigned char>());
}

