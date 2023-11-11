#pragma once

#include <drogon/HttpSimpleController.h>
#include "../models/Comment.h"

using namespace std;
using namespace drogon;

class CommentValidator {
public:
    static bool validateCreateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Comment&comment);

    static bool validateUpdateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Comment&comment);
};
