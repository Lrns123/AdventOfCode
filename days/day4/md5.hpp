#pragma once
#include <openssl/evp.h>
#include <string>
#include <vector>

class MD5
{
    EVP_MD_CTX ctx;

public:
    MD5();
    ~MD5();

    MD5& init();
    MD5& update(const std::string& data);
    std::vector<unsigned char> final();
};