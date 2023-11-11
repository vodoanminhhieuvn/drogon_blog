/**
 *
 *  LoginFilter.cc
 *
 */

#include <drogon/drogon.h>
#include "LoginFilter.h"
#include "../plugins/JwtPlugin.h"

using namespace drogon;

void LoginFilter::doFilter(const HttpRequestPtr&req,
                           FilterCallback&&fcb,
                           FilterChainCallback&&fccb) {
    try {
        if (req->getHeader("Authorization").empty()) {
            Json::Value ret;
            ret["error"] = "missing Authorization header";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k400BadRequest);
            fcb(resp);
            return;
        }

        auto token = req->getHeader("Authorization").substr(7);
        auto* jwtPtr = app().getPlugin<JwtPlugin>();
        auto jwt = jwtPtr->init();
        auto decoded = jwt.decode(token);
        auto userId = stoll(decoded.get_payload_claim("user_id").as_string());
        req->addHeader("user_id", std::to_string(userId));
        fccb();
    }
    catch (jwt::error::token_verification_exception&e) {
        Json::Value error;
        error["error"] = "Invalid token";
        error["error_detail"] = e.what();
        auto resp = HttpResponse::newHttpJsonResponse(error);
        resp->setStatusCode(k400BadRequest);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        fcb(resp);
    }
    catch (const std::runtime_error&e) {
        auto resp = HttpResponse::newHttpResponse();
        LOG_ERROR << e.what();
        resp->setStatusCode(k500InternalServerError);
        fcb(resp);
    }
}
