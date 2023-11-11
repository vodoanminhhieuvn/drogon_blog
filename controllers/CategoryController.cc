#include "CategoryController.h"
#include "../dtos/UserDto.h"
#include "../dtos/PaginationDto.h"
#include "../validators/CategoryValidator.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

void CategoryController::connect() {
    client = app().getDbClient();
}

void CategoryController::createCategory(const HttpRequestPtr&req,
                                        std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<Category> mpCategory(client);

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        Category reqCategory = Category();

        if (string errorField; !CategoryValidator::validateCreateForm(*jsonBody, errorField, reqCategory)) {
            Json::Value error;
            error["error"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
        }

        try {
            auto dbCategory = mpCategory.insertFuture(reqCategory).get();
            Json::Value ret = dbCategory.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            LOG_DEBUG << e.base().what();
            Json::Value error;
            error["error"] = "Database error";
            shared_ptr<HttpResponse> response = handleResponse(
                error, k500InternalServerError);
            callback(response);
        }
    }
    else {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        shared_ptr<HttpResponse> response = handleResponse(
            error, k500InternalServerError);
        callback(response);
    }
}

void CategoryController::getCategory(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<Category> mpCategory(client);

        try {
            auto dbCategories = mpCategory.findAll();

            Json::Value catergoriesJson;
            for (auto&dbCategory: dbCategories) {
                Json::Value postJson;
                postJson = dbCategory.toJson();
                catergoriesJson.append(postJson);
            }

            Json::Value ret;
            ret["results"] = !catergoriesJson.isNull() ? catergoriesJson : Json::Value(Json::arrayValue);

            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            LOG_DEBUG << e.base().what();
            Json::Value error;
            error["error"] = "Database error";
            shared_ptr<HttpResponse> response = handleResponse(
                error, k500InternalServerError);
            callback(response);
        }
    }
    else {
        Json::Value error;
        error["error"] = "Unable to connect to database";
        shared_ptr<HttpResponse> response = handleResponse(
            error, k500InternalServerError);
        callback(response);
    }
}
