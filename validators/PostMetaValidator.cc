#include "PostMetaValidator.h"
#include <string>
#include <regex>

bool PostMetaValidator::validateCreateForm(const Json::Value&req, std::string&errorField,
                                           drogon_model::blog::PostMeta&postMeta) {
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

    postMeta.setContent(content);

    return true;
}

bool PostMetaValidator::validateUpdateForm(const Json::Value&req, std::string&errorField,
                                           drogon_model::blog::PostMeta&postMeta) {
    if (req.isMember("content") && req["content"].isString()) {
        const std::string content = req["content"].asString();

        if (req["content"].asString().length() < 5) {
            errorField = "content is too short";
            return false;
        }
        postMeta.setContent(content);
    }

    return true;
}
