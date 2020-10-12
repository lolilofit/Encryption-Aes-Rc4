//
// Created by User on 12.10.2020.
//

#include "Aes.h"

std::vector<unsigned char> Aes::encrypt() {
    key_expansion();
    add_round_key(0);
    for (int i = 1; i < 10; i++) {
        substitute_bytes(false);
        shift_row(1);
        mix_columns_encrypt();
        add_round_key(i);
    }
    substitute_bytes(false);
    shift_row(1);
    add_round_key(10);

    return state;
}

std::vector<unsigned char> Aes::decrypt_f() {
    key_expansion();
    add_round_key(10);
    shift_row(3);
    substitute_bytes(true);
    for (int i = 9; i > 0; i--) {
        add_round_key(i);
        mix_columns_decrypt();
        shift_row(3);
        substitute_bytes(true);
    }
    add_round_key(0);

    return state;
}

void Aes::key_expansion() {
    for (int j = 1; j < 11; j++) {
        std::vector<unsigned char> key = keys[j - 1];
        std::vector<unsigned char> column = {key[13], key[14], key[15], key[12]};

        for (auto &x: column) {
            std::string s = SBOX[x >> 4][x & 15];
            x = (s[0] - '0') % 39 << 4 | (s[1] - '0') % 39;
        }
        column[0] ^= RCON[j];

        std::transform(begin(column), end(column), begin(key), begin(key), std::bit_xor<unsigned char>());
        std::transform(begin(key) + 4, end(key), begin(key), begin(key) + 4, std::bit_xor<unsigned char>());
        keys.emplace_back(std::move(key));
    }
}

void Aes::add_round_key(int r) {
    std::transform(begin(keys[r]), end(keys[r]), begin(state), begin(state), std::bit_xor<unsigned char>());
}

void Aes::substitute_bytes(bool is_decrypt) {
    std::transform(begin(state), end(state), begin(state), [&](unsigned char x) {
        std::string s = (is_decrypt ? INV_SBOX : SBOX)[x >> 4][x & 15];
        return (s[0] - '0') % 39 << 4 | (s[1] - '0') % 39; });
}

void Aes::shift_row(int r_coef) {
    for (int i = 1; i < 4; i++) {
        std::array<unsigned char, 4> ar = {state[i], state[4 + i], state[8 + i], state[12 + i]};

        std::rotate(begin(ar), begin(ar) + (r_coef * i) % 4, end(ar));
        for (int m = 0; m != 4; m++) { state[m * 4 + i] = ar[m]; }
    }
}

void Aes::mix_columns_encrypt() {
    for (int i = 0; i < 4; i++) {
        const std::array<unsigned char, 4> column = {state[i * 4], state[i * 4 + 1], state[i * 4 + 2], state[i * 4 + 3]};

        state[i * 4] = vector_mult(column, {0x2, 0x3, 0x1, 0x1});
        state[i * 4 + 1] = vector_mult(column, {0x1, 0x2, 0x3, 0x1});
        state[i * 4 + 2] = vector_mult(column, {0x1, 0x1, 0x2, 0x3});
        state[i * 4 + 3] = vector_mult(column, {0x3, 0x1, 0x1, 0x2});
    }
}

void Aes::mix_columns_decrypt() {
    for (int i = 0; i < 4; i++) {
        const std::array<unsigned char, 4> column = {state[i * 4], state[i * 4 + 1], state[i * 4 + 2], state[i * 4 + 3]};
        state[i * 4] = vector_mult(column, {0xe, 0xb, 0xd, 0x9});
        state[i * 4 + 1] = vector_mult(column, {0x9, 0xe, 0xb, 0xd});
        state[i * 4 + 2] = vector_mult(column, {0xd, 0x9, 0xe, 0xb});
        state[i * 4 + 3] = vector_mult(column, {0xb, 0xd, 0x9, 0xe});
    }
}