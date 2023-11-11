#include "PostValidator.h"
#include <string>
#include <regex>

bool PostValidator::validateCreateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Post&post) {
    //? Check if fields exist in the JSON
    if (!req.isMember("title")) {
        errorField = "title is missing";
        return false;
    }

    if (!req.isMember("summary")) {
        errorField = "summary is missing";
        return false;
    }

    if (!req.isMember("slug")) {
        errorField = "slug is missing";
        return false;
    }

    //? Check the data types of the fields
    if (!req["title"].isString()) {
        errorField = "title is not a string";
        return false;
    }

    if (!req["summary"].isString()) {
        errorField = "summary is not a string";
        return false;
    }

    if (!req["slug"].isString()) {
        errorField = "slug is not a string";
        return false;
    }

    const std::string title = req["title"].asString();
    const std::string summary = req["summary"].asString();
    const std::string slug = req["slug"].asString();

    if (title.length() < 5) {
        errorField = "title is too short";
        return false;
    }

    if (summary.length() < 5) {
        errorField = "summary is too short";
        return false;
    }

    post.setTitle(title);
    post.setSummary(summary);
    post.setSlug(slug);

    return true;
}

bool PostValidator::validateUpdateForm(const Json::Value&req, std::string&errorField, drogon_model::blog::Post&post) {
    if (req.isMember("title") && req["title"].isString()) {
        const std::string title = req["title"].asString();

        if (req["title"].asString().length() < 5) {
            errorField = "title is too short";
            return false;
        }
        post.setTitle(title);
    }

    if (req.isMember("summary") && req["summary"].isString()) {
        const std::string summary = req["summary"].asString();

        if (req["summary"].asString().length() < 5) {
            errorField = "summary is too short";
            return false;
        }
        post.setSummary(summary);
    }

    if (req.isMember("slug") && req["slug"].isString()) {
        const std::string slug = req["slug"].asString();

        post.setSlug(slug);
    }

    return true;
}
