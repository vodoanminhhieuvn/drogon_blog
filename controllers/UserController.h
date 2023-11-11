#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"
#include "BaseController.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

class UserController final : public drogon::HttpController<UserController>, public BaseController {
public:
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::get, "/users", HttpMethod::Get, "LoginFilter");
    ADD_METHOD_TO(UserController::getOne, "/users/{1}", HttpMethod::Get, "LoginFilter");
    ADD_METHOD_TO(UserController::updateOne, "/users/{1}", HttpMethod::Put, "LoginFilter");
    ADD_METHOD_TO(UserController::deleteOne, "/users/{1}", HttpMethod::Delete, "LoginFilter");
    ADD_METHOD_TO(UserController::getMe, "/me", HttpMethod::Get, "LoginFilter");
    ADD_METHOD_TO(UserController::updateMe, "/me", HttpMethod::Put, "LoginFilter");
    ADD_METHOD_TO(UserController::deleteMe, "/me", HttpMethod::Delete, "LoginFilter");
  METHOD_LIST_END

  void get(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

  void getOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int userId);

  void updateOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int userId);

  void deleteOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int userId);

  void getMe(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

  void updateMe(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

  void deleteMe(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

private:
  DbClientPtr client;

  void connect();
};
