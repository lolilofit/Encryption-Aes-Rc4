//
// Created by User on 17.10.2020.
//


#include <sstream>
#include "Aes.h"
#include "AesHashing.h"

std::string* AesHashing::hash_f(std::string &message, std::string &key) {
    std::string initial_message;
    Aes aes(initial_message, key);

    std::istringstream message_seq;
    message_seq.str(message);

    char buffer[17];
    buffer[16] = '\0';

    while (true) {
        std::fill(std::begin(buffer), std::begin(buffer) + 16, '\0');
        message_seq.read(buffer, 16);

        std::string mes_chunk(buffer);

        aes.state = {mes_chunk.begin(), mes_chunk.end()};

        std::vector<unsigned char> encoded = aes.encrypt();

        aes.keys = {encoded};

        if (!message_seq.eof()) {
            return new std::string(encoded.begin(), encoded.end());
        }
    }
}


void AesHashing::run_hashing() {
    std::cout << "--------------HASHING---------------" << std::endl;

    std::string key;
    std::cout << "Enter key with length = 11" << std::endl;

    std::cin >> key;

    if (key.size() != 11) {
        std::cout << "Keylen != 11" << std::endl;
        run_hashing();
    }

    std::cout << "Enter message to encrypt" << std::endl;
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);

    std::string *hash_code = hash_f(input, key);

    std::cout << *hash_code;
}
