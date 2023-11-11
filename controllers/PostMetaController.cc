#include "PostMetaController.h"
#include "../validators/PostMetaValidator.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

void PostMetaController::connect() {
    client = app().getDbClient();
}

bool PostMetaController::checkPostOwnership(Mapper<drogon_model::blog::Post>&mpPost,
                                            const int64_t userId,
                                            const int postId,
                                            drogon_model::blog::Post&reqPost) {
    reqPost = mpPost.findByPrimaryKey(postId);

    if (reqPost.getValueOfAuthorId() != userId) {
        return false;
    }

    return true;
}

void PostMetaController::createPostMeta(const HttpRequestPtr&req,
                                        std::function<void(const HttpResponsePtr&)>&&callback,
                                        int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        Mapper<PostMeta> mpPostMeta(client);
        Mapper<drogon_model::blog::Post> mpPost(client);

        drogon_model::blog::Post reqPost = drogon_model::blog::Post();

        if (!checkPostOwnership(mpPost, userId, postId, reqPost)) {
            Json::Value error;
            error["error"] = "Unauthorized";
            shared_ptr<HttpResponse> response = handleResponse(
                error, k401Unauthorized);
            callback(response);
        }

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        PostMeta reqPostMeta = PostMeta();

        if (string errorField; !PostMetaValidator::validateCreateForm(*jsonBody, errorField, reqPostMeta)) {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
        }

        try {
            reqPostMeta.setPostId(postId);
            auto dbPostMeta = mpPostMeta.insertFuture(reqPostMeta).get();
            reqPost.setUpdatedAt(trantor::Date::now());
            Json::Value ret = dbPostMeta.toJson();
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

void PostMetaController::getPostMeta(const HttpRequestPtr&req,
                                     std::function<void(const HttpResponsePtr&)>&&callback,
                                     int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::blog::Post> mpPost(client);

        try {
            auto reqPost = mpPost.findByPrimaryKey(postId);

            Json::Value ret = reqPost.getPost_meta(client).toJson();
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

void PostMetaController::updatePostMeta(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback,
                                        int postId,
                                        int postMetaId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        Mapper<PostMeta> mpPostMeta(client);
        Mapper<drogon_model::blog::Post> mpPost(client);

        drogon_model::blog::Post reqPost = drogon_model::blog::Post();

        if (!checkPostOwnership(mpPost, userId, postId, reqPost)) {
            Json::Value error;
            error["error"] = "Unauthorized";
            shared_ptr<HttpResponse> response = handleResponse(
                error, k401Unauthorized);
            callback(response);
        }


        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        PostMeta reqPostMeta = PostMeta();

        if (string errorField; !PostMetaValidator::validateCreateForm(*jsonBody, errorField, reqPostMeta)) {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
        }

        try {
            auto updatePostMeta = mpPostMeta.findByPrimaryKey(postMetaId);

            if (reqPostMeta.getContent() != nullptr)
                updatePostMeta.setContent(*reqPostMeta.getContent());

            reqPost.setUpdatedAt(trantor::Date::now());

            mpPostMeta.update(updatePostMeta);
            mpPost.update(reqPost);

            Json::Value ret;
            ret["message"] = "Post meta updated";
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            const auto* s = dynamic_cast<const UnexpectedRows *>(&e.base());
            Json::Value error;

            if (s) {
                error["error"] = "Post record not found";
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
