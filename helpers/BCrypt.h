#ifndef DROGONCORE_USER_SERVICE_BCRYPT_H
#define DROGONCORE_USER_SERVICE_BCRYPT_H

#include <string>
#include <drogon/HttpController.h>

class BCrypt
{
public:
    BCrypt() = default;

public:
    static std::string hashPassword(const std::string &password);
    static bool verifyPassword(const std::string &password, const std::string &salt_key_b64);
};

#endif