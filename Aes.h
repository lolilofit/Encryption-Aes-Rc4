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

    std::vector<unsigned char> state;

    std::vector<std::vector<unsigned char>> keys;

    bool decrypt;

    std::vector<unsigned char> encrypt();

    std::vector<unsigned char> decrypt_f();

    void key_expansion();

    void add_round_key(int r);

    void substitute_bytes(bool is_decrypt);

    void shift_row(int r_coef);

    void mix_columns_encrypt();

    void mix_columns_decrypt();

};


#endif //SECURITYLAB3_AES_H
