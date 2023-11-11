#pragma once

#include <drogon/HttpController.h>
#include "../models/Post.h"
#include "../models/PostMeta.h"
#include "BaseController.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

class PostMetaController final : public HttpController<PostMetaController>, public BaseController {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(PostMetaController::createPostMeta, "/me/posts/{1}/meta", HttpMethod::Post, "LoginFilter");
        ADD_METHOD_TO(PostMetaController::getPostMeta, "/me/posts/{1}/meta", HttpMethod::Get, "LoginFilter");
        ADD_METHOD_TO(PostMetaController::updatePostMeta, "/me/posts/{1}/meta/{2}", HttpMethod::Put, "LoginFilter");
    METHOD_LIST_END

    void createPostMeta(const HttpRequestPtr&req,
                        std::function<void(const HttpResponsePtr&)>&&callback,
                        int postId);

    void getPostMeta(const HttpRequestPtr&req,
                     std::function<void(const HttpResponsePtr&)>&&callback,
                     int postId);

    void updatePostMeta(const HttpRequestPtr&req,
                        std::function<void(const HttpResponsePtr&)>&&callback,
                        int postId, int postMetaId);

private:
    DbClientPtr client;

    void connect();

    static bool checkPostOwnership(Mapper<drogon_model::blog::Post>&mpPost,
                                   int64_t userId,
                                   int postId,
                                   drogon_model::blog::Post&reqPost);
};
