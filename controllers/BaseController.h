#pragma once

#include <drogon/HttpSimpleController.h>

using namespace std;
using namespace drogon;
using namespace drogon::orm;

template<typename T>
T fromJson(const Json::Value&) {
    LOG_ERROR << "You must specialize the fromRequest template for the type of "
            << DrClassMap::demangle(typeid(T).name());
    exit(1);
}

class BaseController {
public:
    static void getHeaders(
        const HttpRequestPtr&req,
        function<void(const HttpResponsePtr&)>&&callback);

    static void getByIdHeaders(
        const HttpRequestPtr&req,
        function<void(const HttpResponsePtr&)>&&callback,
        const string&userId);

    static shared_ptr<HttpResponse> handleResponse(
        const Json::Value&responseData, const HttpStatusCode statusCode) {
        auto resp = HttpResponse::newHttpJsonResponse(responseData);
        resp->setStatusCode(statusCode);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        return resp;
    }
};
