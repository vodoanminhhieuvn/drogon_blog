//
// Created by Vo Doan Minh Hieu on 02/11/2023.
//

#pragma once

#include <drogon/HttpSimpleController.h>
#include "../models/User.h"

using namespace std;
using namespace drogon;
using namespace drogon_model::blog;

class UserValidator {
public:
    static bool validateRegisterForm(const Json::Value&req, std::string&errorField, User&user);

    static bool validateLoginForm(const Json::Value&req, std::string&errorField, User&user);
};
