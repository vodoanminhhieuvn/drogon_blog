#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"

using namespace drogon_model::blog;

struct UserTokenDtoResponse {
    std::int64_t id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::string token;

    explicit UserTokenDtoResponse(const User&user);

    [[nodiscard]] Json::Value toJson() const;
};

struct UserDetailsDtoResponse {
    std::int64_t id;
    std::string firstName;
    std::string lastName;
    std::string email;
    bool isDeleted;
    std::string createdAt;
    std::string updatedAt;
    std::string deletedAt;
    std::string lastLogin;

    explicit UserDetailsDtoResponse(const User&user);

    [[nodiscard]] Json::Value toJson() const;
};
