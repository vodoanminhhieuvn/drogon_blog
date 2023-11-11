//
// Created by Vo Doan Minh Hieu on 11/11/2023.
//

#ifndef CATEGORYVALIDATOR_H
#define CATEGORYVALIDATOR_H

#include <drogon/HttpSimpleController.h>
#include "../models/Category.h"

using namespace std;
using namespace drogon;

class CategoryValidator {
public:
    static bool validateCreateForm(const Json::Value&req, std::string&errorField,
                                   drogon_model::blog::Category&category);

    static bool validateGetForm(const Json::Value&req, std::string&errorField,
                                std::vector<int>&categoriesId);

    static bool validateUpdateForm(const Json::Value&req, std::string&errorField,
                                   drogon_model::blog::Category&category);
};


#endif //CATEGORYVALIDATOR_H
