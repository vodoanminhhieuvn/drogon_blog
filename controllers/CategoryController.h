#pragma once

#include <drogon/HttpController.h>
#include "../models/Category.h"
#include "BaseController.h"

using namespace drogon;

class CategoryController final : public HttpController<CategoryController>, public BaseController {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CategoryController::createCategory, "/categories", HttpMethod::Post, "LoginFilter");
        ADD_METHOD_TO(CategoryController::getCategory, "/categories", HttpMethod::Get, "LoginFilter");
    METHOD_LIST_END

    void createCategory(const HttpRequestPtr&req,
                        std::function<void(const HttpResponsePtr&)>&&callback);

    void getCategory(const HttpRequestPtr&req,
                     std::function<void(const HttpResponsePtr&)>&&callback);

private:
    DbClientPtr client;

    void connect();
};
