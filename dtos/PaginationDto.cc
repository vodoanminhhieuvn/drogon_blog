#include "PaginationDto.h"

PaginationDto::PaginationDto(const drogon::HttpRequestPtr&req) {
    page = req->getOptionalParameter<int>("page").value_or(1);
    limit = req->getOptionalParameter<int>("limit").value_or(10);
    sortField = req->getOptionalParameter<std::string>("sort_field").value_or("id");
    auto sortOrder = req->getOptionalParameter<std::string>("sort_order").value_or("asc");

    if (sortOrder == "asc") {
        this->sortOrder = drogon::orm::SortOrder::ASC;
    }
    else if (sortOrder == "desc") {
        this->sortOrder = drogon::orm::SortOrder::DESC;
    }

    pageOffset = (page - 1) * limit;
}

PaginationDtoResponse::PaginationDtoResponse(const PaginationDto&pagination, const int totalRecords) {
    page = pagination.page;
    pageOffset = pagination.pageOffset;
    limit = pagination.limit;
    this->totalRecords = totalRecords;
    totalPages = (totalRecords + pagination.limit - 1) / pagination.limit;
    sortField = pagination.sortField;
    sortOrder = pagination.sortOrder;
}

Json::Value PaginationDtoResponse::toJson() const {
    Json::Value ret;
    ret["page"] = page;
    ret["page_offset"] = pageOffset;
    ret["limit"] = limit;
    ret["total_records"] = totalRecords;
    ret["total_pages"] = totalPages;
    ret["sort_field"] = sortField;
    ret["sort_order"] = sortOrder == drogon::orm::SortOrder::ASC ? "asc" : "desc";
    return ret;
}
