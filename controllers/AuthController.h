#pragma once

#include <drogon/HttpController.h>
#include "../models/User.h"
#include "BaseController.h"
#include "dtos/UserDto.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

class AuthController final : public drogon::HttpController<AuthController>, public BaseController {
public:
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(AuthController::registerUser, "/auth/register", HttpMethod::Post);
    ADD_METHOD_TO(AuthController::loginUser, "/auth/login", HttpMethod::Post);
  METHOD_LIST_END

  void registerUser(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

  void loginUser(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

private:
  DbClientPtr client;

  void connect();

  static bool isUserAvailable(const User&user, Mapper<User>&mp);
};
