#include "UserController.h"
#include "../dtos/PaginationDto.h"
#include "../dtos/UserDto.h"
#include <drogon/orm/DbClient.h>
// Add definition of your processing function here

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

template<>
inline User fromJson(const Json::Value&json) {
    auto user = User(json);
    return user;
}

void UserController::connect() {
    client = app().getDbClient();
}

//? GET /users/
void UserController::get(const HttpRequestPtr&req,
                         std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        auto paginationDto = PaginationDto(req);

        Mapper<User> mp(client);

        try {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM user_");

            if (result.empty()) {
                Json::Value ret;
                Json::Value pageRet = PaginationDtoResponse(paginationDto, 0).toJson();
                ret["pagination"] = pageRet;
                ret["results"] = Json::Value(Json::arrayValue);
                shared_ptr<HttpResponse> response = handleResponse(
                    ret, k200OK);
                callback(response);
            }

            auto totalRecords = result[0][0].as<int>();

            auto dbUsers = mp.orderBy(paginationDto.sortField, paginationDto.sortOrder)
                    .limit(paginationDto.limit)
                    .offset(paginationDto.pageOffset)
                    .findAll();

            Json::Value userJson;
            for (auto&user: dbUsers) {
                userJson.append(UserDetailsDtoResponse(user).toJson());
            }

            Json::Value ret;
            Json::Value pageRet = PaginationDtoResponse(paginationDto, totalRecords).toJson();

            ret["pagination"] = pageRet;
            ret["results"] = !userJson.isNull() ? userJson : Json::Value(Json::arrayValue);

            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            Json::Value error;
            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

//? GET /users/{id}
void UserController::getOne(const HttpRequestPtr&req,
                            std::function<void(const HttpResponsePtr&)>&&callback,
                            int userId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<User> mp(client);

        try {
            auto user = mp.findByPrimaryKey(userId);

            Json::Value ret;
            ret = user.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "Record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

//? PUT /users/{id}
void UserController::updateOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback,
                               int userId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();

        User user = fromJson<User>(*jsonBody);

        Mapper<User> mp(client);

        try {
            auto updateUser = mp.findByPrimaryKey(userId);

            if (user.getIntro() != nullptr)
                updateUser.setIntro(*user.getIntro());
            if (user.getFirstName() != nullptr)
                updateUser.setFirstName(*user.getFirstName());
            if (user.getLastName() != nullptr)
                updateUser.setLastName(*user.getLastName());
            if (user.getProfile() != nullptr)
                updateUser.setProfile(*user.getProfile());
            updateUser.setUpdatedAt(trantor::Date::now());

            mp.update(updateUser);

            Json::Value ret;
            ret = updateUser.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

//? DELETE /users/{id}
void UserController::deleteOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback,
                               int userId) {
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    connect();

    if (client) {
        Mapper<User> mp(client);

        try {
            auto user = mp.findByPrimaryKey(userId);

            user.setIsDeleted(true);
            user.setDeletedAt(trantor::Date::now());

            mp.update(user);

            Json::Value ret;
            ret = user.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

// ------------------------------

//? GET /me
void UserController::getMe(const HttpRequestPtr&req,
                           std::function<void(const HttpResponsePtr&)>&&callback) {
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    int64_t userId = stoll(req->getHeader("user_id"));

    connect();

    if (client) {
        Mapper<User> mp(client);

        try {
            auto user = mp.findByPrimaryKey(userId);

            Json::Value ret;
            ret = user.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "Record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

//? PUT /me
void UserController::updateMe(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();

        int64_t userId = stoll(req->getHeader("user_id"));

        User user = fromJson<User>(*jsonBody);

        Mapper<User> mp(client);

        try {
            auto updateUser = mp.findByPrimaryKey(userId);

            if (user.getIntro() != nullptr)
                updateUser.setIntro(*user.getIntro());
            if (user.getFirstName() != nullptr)
                updateUser.setFirstName(*user.getFirstName());
            if (user.getLastName() != nullptr)
                updateUser.setLastName(*user.getLastName());
            if (user.getProfile() != nullptr)
                updateUser.setProfile(*user.getProfile());
            updateUser.setUpdatedAt(trantor::Date::now());

            mp.update(updateUser);

            Json::Value ret;
            ret = updateUser.toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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

//? DELETE /me
void UserController::deleteMe(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback) {
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    int userId = stoi(req->getHeader("user_id"));

    connect();

    if (client) {
        Mapper<User> mp(client);

        try {
            mp.deleteByPrimaryKey(userId);

            Json::Value ret;
            ret["message"] = "User deleted successfully";
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "User record not found";
                error["error_detail"] = e.base().what();
                shared_ptr<HttpResponse> response = handleResponse(
                    error, k404NotFound);
                callback(response);
            }

            error["error"] = "Database error";
            error["error_detail"] = e.base().what();
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
