//
// Created by Vo Doan Minh Hieu on 11/11/2023.
//

#include "CategoryValidator.h"
#include <string>
#include <regex>

bool CategoryValidator::validateCreateForm(const Json::Value&req, std::string&errorField,
                                           drogon_model::blog::Category&category) {
    //? Check if fields exist in the JSON
    if (!req.isMember("title")) {
        errorField = "title is missing";
        return false;
    }

    if (!req.isMember("content")) {
        errorField = "content is missing";
        return false;
    }

    if (!req.isMember("slug")) {
        errorField = "slug is missing";
        return false;
    }

    //? Check data types of the fields
    if (!req["title"].isString()) {
        errorField = "title is not a string";
        return false;
    }

    if (!req["content"].isString()) {
        errorField = "content is not a string";
        return false;
    }

    if (!req["slug"].isString()) {
        errorField = "slug is not a string";
        return false;
    }

    const std::string title = req["title"].asString();
    const std::string content = req["content"].asString();
    const std::string slug = req["slug"].asString();

    category.setContent(content);
    category.setTitle(title);
    category.setSlug(slug);

    return true;
}

bool CategoryValidator::validateGetForm(const Json::Value&req, std::string&errorField, std::vector<int>&categoriesId) {
    if (req.isMember("categories") && req["categories"].isArray()) {
        for (const auto&element: req["categories"]) {
            if (!element.isInt()) {
                errorField = "categories is not an array of integers";
                return false;
            }
            categoriesId.push_back(element.asInt());
        }
    }

    return true;
}


