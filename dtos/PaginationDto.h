#pragma once

#include <string>
#include <drogon/HttpController.h>
#include <drogon/orm/Mapper.h>

struct PaginationDto {
    int page;
    int pageOffset;
    int limit;
    std::string sortField;
    drogon::orm::SortOrder sortOrder;

    explicit PaginationDto(const drogon::HttpRequestPtr&req);
};

struct PaginationDtoResponse {
    int page;
    int pageOffset;
    int limit;
    int totalPages;
    int totalRecords;
    std::string sortField;
    drogon::orm::SortOrder sortOrder;

    explicit PaginationDtoResponse(const PaginationDto&pagination, int totalRecords);

    [[nodiscard]] Json::Value toJson() const;
};
