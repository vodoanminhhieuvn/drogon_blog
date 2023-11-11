//
// Created by Vo Doan Minh Hieu on 02/11/2023.
//

#pragma once

#include <drogon/HttpSimpleController.h>
#include "../models/Post.h"

using namespace std;
using namespace drogon;

class PostValidator {
public:
    static bool validateCreateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Post&post);

    static bool validateUpdateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Post&post);
};
