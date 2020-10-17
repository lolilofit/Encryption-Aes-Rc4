//
// Created by User on 04.10.2020.
//

#ifndef SECURITYLAB3_RC4_H
#define SECURITYLAB3_RC4_H

#include <iostream>

class Rc4 {
public:
    static void init_s(unsigned const char *key, int key_len, unsigned char *s) {
        int val = 0;
        unsigned char tmp;

        for (int i = 0; i < 256; i++)
            s[i] = i;
        for (int i = 0; i < 256; i++) {
            val = (val + key[i % key_len] + s[i]) % 256;

            tmp = s[i];
            s[i] = s[val];
            s[val] = tmp;
        }
    }

    static unsigned char generate_seq(unsigned char *s, int &a, int &b) {
        a = (a + 1) % 256;
        b = (b + s[a]) % 256;

        unsigned char tmp = s[a];
        s[a] = s[b];
        s[b] = tmp;

        return s[(s[a] + s[b]) % 256];
    }

    static void encrypt(unsigned char *result, unsigned const char *input, int input_len, unsigned char *s) {
        int a = 0;
        int b = 0;

        for (int i = 0; i < input_len; i++)
            result[i] = (unsigned char) (input[i] ^ generate_seq(s, a, b));
    }

    static unsigned char* run_rc4_base(unsigned const char *key, unsigned const char *input, int input_len, int l) {
        auto *s = new unsigned char[257];
        s[256] = '\0';
        init_s(key, l, s);

        auto *result = new unsigned char[input_len + 1];
        result[input_len] = '\0';

        encrypt(result, input, input_len, s);

        std::cout << result << std::endl;
        return result;
    }

    static void run_rc4() {
        std::cout << "----------Rc4--------------" << std::endl;

        int l = 3;
        std::cout << "enter key with length =  " << l << std::endl;
        auto *s_key = new unsigned char[l];
        std::cin >> s_key;

        std::cout << "Enter message to encrypt" << std::endl;
        std::string input;
        std::cin.ignore();
        std::getline(std::cin, input);

        unsigned char *result = run_rc4_base(s_key, reinterpret_cast<const unsigned char *>(input.c_str()),
                                             input.size(), l);

        run_rc4_base(s_key, result, input.size(), l);
    }
};

#endif //SECURITYLAB3_RC4_H
