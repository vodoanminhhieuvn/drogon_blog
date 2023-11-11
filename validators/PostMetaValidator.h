#pragma once

#include <drogon/HttpSimpleController.h>
#include "../models/PostMeta.h"

using namespace std;
using namespace drogon;

class PostMetaValidator {
public:
    static bool validateCreateForm(const Json::Value&req, std::string&errorField,
                                   drogon_model::blog::PostMeta&postMeta);

    static bool validateUpdateForm(const Json::Value&req, std::string&errorField,
                                   drogon_model::blog::PostMeta&postMeta);
};
