#pragma once

#include <drogon/HttpController.h>
#include "BaseController.h"

using namespace drogon;
using namespace drogon::orm;

class CommentController final : public HttpController<CommentController>, public BaseController {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CommentController::createPostComment, "/comments/posts/{1}", HttpMethod::Post, "LoginFilter");
        ADD_METHOD_TO(CommentController::getPostComment, "/comments/posts/{1}", HttpMethod::Get, "LoginFilter");
    METHOD_LIST_END

    void createPostComment(const HttpRequestPtr&req,
                           std::function<void(const HttpResponsePtr&)>&&callback,
                           int postId);

    void getPostComment(const HttpRequestPtr&req,
                        std::function<void(const HttpResponsePtr&)>&&callback,
                        int postId);

private:
    DbClientPtr client;

    void connect();
};
