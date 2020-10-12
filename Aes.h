//
// Created by User on 12.10.2020.
//

#ifndef SECURITYLAB3_AES_H
#define SECURITYLAB3_AES_H

#include <utility>
#include <vector>
#include <string>
#include "AesUtils.h"

class Aes {
public:
    Aes(const std::string& text, const std::string& cipher, bool decrypt = false)
            : state({begin(text), end(text)}), keys({{begin(cipher), end(cipher)}}), decrypt(decrypt) {}
    Aes() = default;

    Aes(const Aes &) = default;

    std::vector<byte_t> state;

    std::vector<std::vector<byte_t>> keys;

    bool decrypt;

    std::vector<unsigned char> encrypt();

    std::vector<unsigned char> decrypt_f();

    void key_expansion();

    void add_round_key(int r);

    void substitute_bytes();

    void shift_rows();

    void shift_row(std::array<byte_t, 4>&& row, int k, int j);

    void mix_columns();

    byte_t hex(unsigned char ch) { return (ch - '0') % 39; }

    byte_t sbox(byte_t x, bool decrypt = false) {
        std::string s = (decrypt ? INV_SBOX : SBOX)[x >> 4][x & 15];
        return hex(s[0]) << 4 | hex(s[1]);
    }
};


#endif //SECURITYLAB3_AES_H
