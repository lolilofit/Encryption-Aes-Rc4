#include "Aes.h"
#include "Rc4.h"
#include "AesHashing.h"

int main(int argc, char *argv[]) {
    AesHashing::run_hashing();

    Aes::run_aes(argc, argv);

    Rc4::run_rc4();

    return 0;
}
