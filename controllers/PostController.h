#pragma once

#include <drogon/HttpController.h>
#include "../models/PostCategory.h"
#include "BaseController.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

class PostController final : public HttpController<PostController>, public BaseController {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PostController::create, "/posts?userId={1}", HttpMethod::Post, "LoginFilter");
        ADD_METHOD_TO(PostController::get, "/posts", HttpMethod::Get, "LoginFilter");
        ADD_METHOD_TO(PostController::getOne, "/posts/{1}", HttpMethod::Get, "LoginFilter");
        ADD_METHOD_TO(PostController::update, "/posts/{1}", HttpMethod::Put, "LoginFilter");
        ADD_METHOD_TO(PostController::deleteOne, "/posts/{1}", HttpMethod::Delete, "LoginFilter");
        ADD_METHOD_TO(PostController::createMyPost, "/me/posts", HttpMethod::Post, "LoginFilter");
        ADD_METHOD_TO(PostController::getMyPosts, "/me/posts", HttpMethod::Get, "LoginFilter");
    METHOD_LIST_END

    void create(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback,
                int userId);

    void createMyPost(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

    void get(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

    void getMyPosts(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback);

    void getOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int postId);

    void update(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int postId);

    void deleteOne(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback, int postId);

private:
    DbClientPtr client;

    void connect();
};
