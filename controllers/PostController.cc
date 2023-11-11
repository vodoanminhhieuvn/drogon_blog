#include "PostController.h"
#include "../dtos/PaginationDto.h"
#include "../dtos/UserDto.h"
#include "../validators/PostValidator.h"
#include "../validators/CategoryValidator.h"

// Add definition of your processing function here

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

void PostController::connect() {
    client = app().getDbClient();
}

void PostController::create(const HttpRequestPtr&req, std::function<void(const HttpResponsePtr&)>&&callback,
                            int userId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        drogon_model::blog::Post post = drogon_model::blog::Post();

        if (string errorField; !PostValidator::validateCreateForm(*jsonBody, errorField, post)) {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
        }

        Mapper<drogon_model::blog::Post> mp(client);

        try {
            post.setCreatedAt(trantor::Date::now());
            post.setAuthorId(userId);
            auto dbPost = mp.insertFuture(post).get();
            Json::Value ret = dbPost.toJson();
            ret["author"] = UserDetailsDtoResponse(dbPost.getUser(client)).toJson();
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

void PostController::get(const HttpRequestPtr&req,
                         std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        auto paginationDto = PaginationDto(req);

        Mapper<drogon_model::blog::Post> mp(client);

        try {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM post");

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

            auto dbPosts = mp.orderBy(paginationDto.sortField, paginationDto.sortOrder)
                    .limit(paginationDto.limit)
                    .offset(paginationDto.pageOffset)
                    .findAll();

            Json::Value postsJson;
            for (auto&dbPost: dbPosts) {
                Json::Value postJson;
                postJson = dbPost.toJson();
                postJson["author"] = UserDetailsDtoResponse(dbPost.getUser(client)).toJson();
                postsJson.append(postJson);
            }

            Json::Value ret;
            Json::Value pageRet = PaginationDtoResponse(paginationDto, totalRecords).toJson();

            ret["pagination"] = pageRet;
            ret["results"] = !postsJson.isNull() ? postsJson : Json::Value(Json::arrayValue);

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

void PostController::getOne(const HttpRequestPtr&req,
                            std::function<void(const HttpResponsePtr&)>&&callback,
                            int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::blog::Post> mp(client);

        try {
            auto dbPost = mp.findByPrimaryKey(postId);
            Json::Value ret = dbPost.toJson();
            ret["author"] = UserDetailsDtoResponse(dbPost.getUser(client)).toJson();
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k200OK);
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

void PostController::update(const HttpRequestPtr&req,
                            std::function<void(const HttpResponsePtr&)>&&callback,
                            int postId) {
    std::string method = req->methodString();
    LOG_DEBUG << "Received request: " << method << " " << req->path();

    shared_ptr<Json::Value> jsonBody = req->getJsonObject();
    auto reqPost = drogon_model::blog::Post();

    if (string errorField; !PostValidator::validateUpdateForm(*jsonBody, errorField, reqPost)) {
        Json::Value error;
        error["error"] = "Invalid form";
        error["error_detail"] = errorField;
        shared_ptr<HttpResponse> response = handleResponse(
            error, k400BadRequest);
        callback(response);
        return;
    }

    connect();

    if (client) {
        Mapper<drogon_model::blog::Post> mp(client);

        try {
            auto updatePost = mp.findByPrimaryKey(postId);

            if (reqPost.getTitle() != nullptr)
                updatePost.setTitle(*reqPost.getTitle());
            if (reqPost.getSummary() != nullptr)
                updatePost.setSummary(*reqPost.getSummary());
            if (reqPost.getSlug() != nullptr)
                updatePost.setSlug(*reqPost.getSlug());
            updatePost.setUpdatedAt(trantor::Date::now());

            mp.update(updatePost);
            Json::Value ret = updatePost.toJson();
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

void PostController::deleteOne(const HttpRequestPtr&req,
                               std::function<void(const HttpResponsePtr&)>&&callback,
                               int postId) {
    connect();

    if (client) {
        std::string method = req->methodString();

        LOG_DEBUG << "Received request: " << method << " " << req->path();

        Mapper<drogon_model::blog::Post> mp(client);

        try {
            mp.deleteByPrimaryKey(postId);

            Json::Value ret;
            ret["message"] = "Post deleted successfully";
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

// ------------------------------

void PostController::createMyPost(const HttpRequestPtr&req,
                                  std::function<void(const HttpResponsePtr&)>&&callback) {
    connect();

    if (client) {
        std::string method = req->methodString();
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        shared_ptr<Json::Value> jsonBody = req->getJsonObject();
        drogon_model::blog::Post post = drogon_model::blog::Post();
        std::vector<int> categoriesId;

        if (string errorField; !PostValidator::validateCreateForm(*jsonBody, errorField, post)) {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
            return;
        }

        if (string errorField; !CategoryValidator::validateGetForm(*jsonBody, errorField, categoriesId)) {
            Json::Value error;
            error["error"] = "Invalid form";
            error["error_detail"] = errorField;
            shared_ptr<HttpResponse> response = handleResponse(
                error, k400BadRequest);
            callback(response);
            return;
        }

        Mapper<drogon_model::blog::Post> mpPost(client);
        Mapper<PostCategory> mpPostCategory(client);

        try {
            post.setCreatedAt(trantor::Date::now());
            post.setAuthorId(userId);
            auto dbPost = mpPost.insertFuture(post).get();

            Json::Value catergoriessJson;


            if (!categoriesId.empty()) {
                for (auto categoryId: categoriesId) {
                    PostCategory postCategory = PostCategory();
                    postCategory.setCategoryId(categoryId);
                    postCategory.setPostId(dbPost.getValueOfId());
                    mpPostCategory.insert(postCategory);
                }

                for (const auto&[category, postCatergory]: dbPost.getCategories(client)) {
                    catergoriessJson.append(category.toJson());
                }
            }

            Json::Value ret = dbPost.toJson();
            ret["categories"] = !catergoriessJson.isNull() ? catergoriessJson : Json::Value(Json::arrayValue);
            shared_ptr<HttpResponse> response = handleResponse(
                ret, k201Created);
            callback(response);
        }
        catch (const DrogonDbException&e) {
            LOG_DEBUG << e.base().what();

            Json::Value error;
            error["error"] = "Database error";
            error["message"] = e.base().what();
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

void PostController::getMyPosts(const HttpRequestPtr&req,
                                std::function<void(const HttpResponsePtr&)>&&callback) {
    std::string method = req->methodString();

    connect();

    if (client) {
        LOG_DEBUG << "Received request: " << method << " " << req->path();

        int64_t userId = stoll(req->getHeader("user_id"));

        auto paginationDto = PaginationDto(req);

        Mapper<drogon_model::blog::Post> mp(client);

        try {
            auto result = client->execSqlSync("SELECT COUNT(*) FROM post WHERE author_id=$1", userId);

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

            auto dbPosts = mp.orderBy(paginationDto.sortField, paginationDto.sortOrder)
                    .limit(paginationDto.limit)
                    .offset(paginationDto.pageOffset)
                    .findBy(Criteria(Post::Cols::_author_id, CompareOperator::EQ, userId));

            Json::Value postsJson;
            for (auto&dbPost: dbPosts) {
                Json::Value postJson;
                postJson = dbPost.toJson();
                postJson["author"] = UserDetailsDtoResponse(dbPost.getUser(client)).toJson();

                Json::Value catergoriessJson;

                for (const auto&[category, postCatergory]: dbPost.getCategories(client)) {
                    catergoriessJson.append(category.toJson());
                }

                postJson["categories"] = !catergoriessJson.isNull() ? catergoriessJson : Json::Value(Json::arrayValue);

                postsJson.append(postJson);
            }

            Json::Value ret;
            Json::Value pageRet = PaginationDtoResponse(paginationDto, totalRecords).toJson();

            ret["pagination"] = pageRet;
            ret["results"] = !postsJson.isNull() ? postsJson : Json::Value(Json::arrayValue);

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
    }
}
