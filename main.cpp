#include <array>
#include <sstream>
#include "Aes.h"
#include "Rc4.h"

std::string *hash_f(std::string &message, std::string &key) {
    std::string initial_message;
    Aes aes(initial_message, key);

    char buffer[17];
    buffer[16] = '\0';

    std::istringstream message_seq;
    message_seq.str(message);

    int count_readen = 0;

    while (true) {
        std::fill(std::begin(buffer), std::begin(buffer) + 16, ' ');
        buffer[16] = '\0';

        message_seq.read(buffer, 16);
        count_readen += 16;

        std::string mes_chunk(buffer);

        aes.state = {mes_chunk.begin(), mes_chunk.end()};

        std::vector<unsigned char> encoded = aes.encrypt();

        aes.keys = {encoded};

        if (count_readen > message.size()) {
            return new std::string(encoded.begin(), encoded.end());
        }
    }
}


void run_hashing() {
    std::cout << std::endl << "--------------HASHING---------------" << std::endl;

    std::cout << "Enter key with length = 11" << std::endl;

    std::string key;
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

int main(int argc, char *argv[]) {
    run_hashing();

    Aes::run_aes(argc, argv);

    Rc4::run_rc4();

    return 0;
}
