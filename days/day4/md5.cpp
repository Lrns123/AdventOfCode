#include "md5.hpp"

MD5::MD5()
{
    EVP_MD_CTX_init(&ctx);
    init();
}

MD5::~MD5()
{
    EVP_MD_CTX_cleanup(&ctx);
}

MD5& MD5::init()
{
    EVP_DigestInit_ex(&ctx, EVP_md5(), nullptr);
    return *this;
}

MD5& MD5::update(const std::string& data)
{
    EVP_DigestUpdate(&ctx, data.c_str(), data.length());
    return *this;
}

std::vector<unsigned char> MD5::final()
{
    unsigned size = EVP_MD_CTX_size(&ctx);
    std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);

    EVP_DigestFinal_ex(&ctx, hash.data(), &size);
    hash.resize(size);

    return hash;
}
