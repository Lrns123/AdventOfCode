#include <openssl/evp.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

class MD5
{
    EVP_MD_CTX ctx;

public:
    MD5()
    {
        EVP_MD_CTX_init(&ctx);
        EVP_DigestInit_ex(&ctx, EVP_md5(), nullptr);
    }

    ~MD5()
    {
        EVP_MD_CTX_cleanup(&ctx);
    }

    MD5 &update(const std::string &data)
    {
        EVP_DigestUpdate(&ctx, data.c_str(), data.length());
        return *this;
    }

    std::vector<unsigned char> final()
    {
        unsigned size = EVP_MD_CTX_size(&ctx);
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);

        EVP_DigestFinal_ex(&ctx, hash.data(), &size);
        hash.resize(size);

        return std::move(hash);
    }
};

bool checkMatch(const std::vector<unsigned char> &hash)
{
    return hash[0] == 0 && hash[1] == 0 && hash[2] >> 4 == 0;
}

std::string toHex(const std::vector<unsigned char> &input)
{
    std::ostringstream ss;

    ss << std::hex << std::setfill('0');

    for (auto ch : input)
        ss << std::setw(2) << static_cast<int>(ch);

    return ss.str();    
}

int main(int, char **)
{
    std::string key;
    std::cin >> key;

    size_t number = 0;

    while (true)
    {
        std::ostringstream stream;
        stream << key << number++;

        auto data = stream.str();

        auto hash = MD5().update(data).final();

        if (checkMatch(hash))
        {
            std::cout << "Hit: " << data << ", Hash:" << toHex(hash) << std::endl;
            break;
        }
    }
}