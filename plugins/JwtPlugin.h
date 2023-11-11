#pragma once

#include <drogon/plugins/Plugin.h>
#include "Jwt.h"

class JwtPlugin final : public drogon::Plugin<JwtPlugin> {
public:
    void initAndStart(const Json::Value&config) override;

    void shutdown() override;

    [[nodiscard]] auto init() const -> Jwt;

private:
    Json::Value config;
};
