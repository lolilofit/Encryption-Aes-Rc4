//
// Created by User on 12.10.2020.
//

#include "Aes.h"

std::vector<unsigned char> Aes::encrypt() {
    key_expansion();
    add_round_key(0);
    for (int i = 1; i < 10; i++) {
        substitute_bytes();
        shift_rows();
        mix_columns();
        add_round_key(i);
    }
    substitute_bytes();
    shift_rows();
    add_round_key(10);

    return state;
}

std::vector<unsigned char> Aes::decrypt_f() {
    key_expansion();
    add_round_key(10);
    shift_rows();
    substitute_bytes();
    for (int i = 9; i != 0; --i) {
        add_round_key(i);
        mix_columns();
        shift_rows();
        substitute_bytes();
    }
    add_round_key(0);

    return state;
}

void Aes::key_expansion() {
    for (int j = 1; j != 11; j++) {
        std::vector<byte_t> key = keys[j - 1];
        std::vector<byte_t> column = {key[13], key[14], key[15], key[12]};
        for (auto &x: column) x = sbox(x);
        column[0] ^= RCON[j];

        std::transform(begin(column), end(column), begin(key), begin(key), std::bit_xor<byte_t>());
        std::transform(begin(key) + 4, end(key), begin(key), begin(key) + 4, std::bit_xor<byte_t>());
        keys.emplace_back(std::move(key));
    }
}

void Aes::add_round_key(int r) {
    std::transform(begin(keys[r]), end(keys[r]), begin(state), begin(state), std::bit_xor<byte_t>());
}

void Aes::substitute_bytes() {
    std::transform(begin(state), end(state), begin(state), [&](byte_t x) { return sbox(x, decrypt); });
}

void Aes::shift_rows() {
    int k = decrypt ? 3 : 1; // coef for rotation point
    for (int i = 1; i != 4; ++i)
        shift_row({state[i], state[4+i], state[8+i], state[12+i]}, (k*i) % 4, i);
}

void Aes::shift_row(std::array<byte_t, 4>&& row, int k, int j) {
    std::rotate(begin(row), begin(row)+k, end(row));
    for (int i = 0; i != 4; ++i) { state[i*4+j] = row[i]; }
}

void Aes::mix_columns() {
    for (int i = 0; i != 4; i++) {
        const std::array<byte_t, 4> column = {state[i*4], state[i*4+1], state[i*4+2], state[i*4+3]};
        if (!decrypt) {
            state[i*4] = vector_mult(column, { 0x2, 0x3, 0x1, 0x1 });
            state[i*4+1] = vector_mult(column, { 0x1, 0x2, 0x3, 0x1 });
            state[i*4+2] = vector_mult(column, { 0x1, 0x1, 0x2, 0x3 });
            state[i*4+3] = vector_mult(column, { 0x3, 0x1, 0x1, 0x2 });
        } else {
            state[i*4] = vector_mult(column, { 0xe, 0xb, 0xd, 0x9 });
            state[i*4+1] = vector_mult(column, { 0x9, 0xe, 0xb, 0xd });
            state[i*4+2] = vector_mult(column, { 0xd, 0x9, 0xe, 0xb });
            state[i*4+3] = vector_mult(column, { 0xb, 0xd, 0x9, 0xe });
        }
    }
}