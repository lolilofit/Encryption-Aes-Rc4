#include <array>
#include "Aes.h"

int main() {
    std::string mes = "HellHellHellHell";
    std::string key = "keykeykeyke";

    Aes aes(mes, key);

    std::vector<unsigned char> encrypted = aes.encrypt();
    //std::cout << encrypted << std::endl;

    //Aes aes_d(encrypted, key, true);
    aes.decrypt = true;
    std::vector<unsigned char> res = aes.decrypt_f();
    std::string res_s(res.begin(), res.end());
    std::cout << res_s;

    return 0;
}
