//
// Created by User on 17.10.2020.
//

#ifndef SECURITYLAB3_AESHASHING_H
#define SECURITYLAB3_AESHASHING_H


#include <string>

class AesHashing {
public:
    static void run_hashing();

    static std::string *hash_f(std::string &message, std::string &key);
};


#endif //SECURITYLAB3_AESHASHING_H
