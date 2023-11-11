#include "CommentValidator.h"
#include <string>
#include <regex>

bool CommentValidator::validateCreateForm(const Json::Value&req, std::string&errorField,
                                          drogon_model::blog::Comment&comment) {
    //? Check if fields exist in the JSON
    if (!req.isMember("content")) {
        errorField = "content is missing";
        return false;
    }

    //? Check the data types of the fields
    if (!req["content"].isString()) {
        errorField = "content is not a string";
        return false;
    }

    const std::string content = req["content"].asString();

    comment.setContent(content);

    return true;
}

bool CommentValidator::validateUpdateForm(const Json::Value&req, std::string&errorField,
                                          drogon_model::blog::Comment&comment) {
    if (req.isMember("content") && req["content"].isString()) {
        const std::string content = req["content"].asString();

        comment.setContent(content);
    }

    return true;
}
