#include <array>
#include <fstream>
#include "Aes.h"

void run_encode_decode_cycle(std::string &filename) {
    std::string key = "keykeykeyke";

    std::fstream file;
    file.open (filename, std::fstream::in);

    char buffer[17];
    buffer[16] = '\0';

    while(!file.eof()) {
        file.read(buffer, 16);
        std::string mes(buffer);

        Aes aes(mes, key);

        std::vector<unsigned char> encrypted = aes.encrypt();
        std::string encrypted_s(encrypted.begin(), encrypted.end());
        std::cout << encrypted_s << std::endl;

        Aes aes_d(encrypted_s, key);
        std::vector<unsigned char> res = aes.decrypt_f();
        std::string res_s(res.begin(), res.end());
        std::cout << res_s << std::endl;

        std::fill(std::begin(buffer), std::begin(buffer) + 16, '\0');
    }

    file.close();
}

int main() {
    std::string filename = "C:\\Users\\User\\CLionProjects\\securityLab3\\file.txt";

    run_encode_decode_cycle(filename);
    return 0;
}
