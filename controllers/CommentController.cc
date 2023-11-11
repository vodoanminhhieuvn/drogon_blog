#include "CommentController.h"
#include "../dtos/UserDto.h"
#include "../dtos/PaginationDto.h"
#include "../validators/CommentValidator.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

void CommentController::connect() {
    client = app().getDbClient();
}

void CommentController::createPostComment(const HttpRequestPtr&req,
                                          std::function<void(const HttpResponsePtr&)>&&callback,
                                          int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        Mapper<Comment> mpComment(client);

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        Comment reqComment = Comment();

        if (string errorField; !CommentValidator::validateCreateForm(*jsonBody, errorField, reqComment)) {
            Json::Value error;
            error["error"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
        }

        try {
            reqComment.setUserId(userId);
            reqComment.setPostId(postId);
            reqComment.setCreatedAt(trantor::Date::now());
            auto dbComment = mpComment.insertFuture(reqComment).get();
            Json::Value ret = dbComment.toJson();
            ret["user"] = UserDetailsDtoResponse(dbComment.getUser(client)).toJson();
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

void CommentController::getPostComment(const HttpRequestPtr&req,
                                       std::function<void(const HttpResponsePtr&)>&&callback,
                                       int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        auto paginationDto = PaginationDto(req);

        Mapper<Comment> mpComment(client);

        try {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM comment WHERE post_id=$1",
                                              static_cast<int64_t>(postId));

            if (result.empty()) {
                Json::Value ret;
                Json::Value pageRet = PaginationDtoResponse(paginationDto, 0).toJson();
                ret["pagination"] = pageRet;
                ret["results"] = Json::Value(Json::arrayValue);
                shared_ptr<HttpResponse> response = handleResponse(
                    ret, k200OK);
                callback(response);
            }

            int totalRecords = result[0]["count"].as<int>();

            auto dbComments = mpComment.orderBy(paginationDto.sortField, paginationDto.sortOrder)
                    .limit(paginationDto.limit)
                    .offset(paginationDto.pageOffset)
                    .findBy(Criteria(Comment::Cols::_post_id, CompareOperator::EQ, static_cast<int64_t>(postId)));

            Json::Value commentsJson;
            for (auto&dbComment: dbComments) {
                Json::Value commentJson;
                commentJson = dbComment.toJson();
                commentJson["user"] = UserDetailsDtoResponse(dbComment.getUser(client)).toJson();
                commentJson.removeMember("user_id");
                commentsJson.append(commentJson);
            }

            Json::Value ret;
            Json::Value pageRet = PaginationDtoResponse(paginationDto, totalRecords).toJson();

            ret["pagination"] = pageRet;
            ret["results"] = !commentsJson.isNull() ? commentsJson : Json::Value(Json::arrayValue);

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
