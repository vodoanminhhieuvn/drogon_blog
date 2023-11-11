/**
 *
 *  Tag.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/BaseBuilder.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace blog
{
class Post;
class PostTag;

class Tag
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _title;
        static const std::string _meta_title;
        static const std::string _slug;
        static const std::string _content;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = int64_t;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Tag(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Tag(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Tag(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Tag() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int64_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getId() const noexcept;
    ///Set the value of the column id
    void setId(const int64_t &pId) noexcept;

    /**  For column title  */
    ///Get the value of the column title, returns the default value if the column is null
    const std::string &getValueOfTitle() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getTitle() const noexcept;
    ///Set the value of the column title
    void setTitle(const std::string &pTitle) noexcept;
    void setTitle(std::string &&pTitle) noexcept;

    /**  For column meta_title  */
    ///Get the value of the column meta_title, returns the default value if the column is null
    const std::string &getValueOfMetaTitle() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getMetaTitle() const noexcept;
    ///Set the value of the column meta_title
    void setMetaTitle(const std::string &pMetaTitle) noexcept;
    void setMetaTitle(std::string &&pMetaTitle) noexcept;
    void setMetaTitleToNull() noexcept;

    /**  For column slug  */
    ///Get the value of the column slug, returns the default value if the column is null
    const std::string &getValueOfSlug() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSlug() const noexcept;
    ///Set the value of the column slug
    void setSlug(const std::string &pSlug) noexcept;
    void setSlug(std::string &&pSlug) noexcept;

    /**  For column content  */
    ///Get the value of the column content, returns the default value if the column is null
    const std::string &getValueOfContent() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getContent() const noexcept;
    ///Set the value of the column content
    void setContent(const std::string &pContent) noexcept;
    void setContent(std::string &&pContent) noexcept;
    void setContentToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 5;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
    std::vector<std::pair<Post,PostTag>> getPosts(const drogon::orm::DbClientPtr &clientPtr) const;
    void getPosts(const drogon::orm::DbClientPtr &clientPtr,
                  const std::function<void(std::vector<std::pair<Post,PostTag>>)> &rcb,
                  const drogon::orm::ExceptionCallback &ecb) const;
  private:
    friend drogon::orm::Mapper<Tag>;
    friend drogon::orm::BaseBuilder<Tag, true, true>;
    friend drogon::orm::BaseBuilder<Tag, true, false>;
    friend drogon::orm::BaseBuilder<Tag, false, true>;
    friend drogon::orm::BaseBuilder<Tag, false, false>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Tag>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int64_t> id_;
    std::shared_ptr<std::string> title_;
    std::shared_ptr<std::string> metaTitle_;
    std::shared_ptr<std::string> slug_;
    std::shared_ptr<std::string> content_;
    struct MetaData
    {
        const std::string colName_;
        const std::string colType_;
        const std::string colDatabaseType_;
        const ssize_t colLength_;
        const bool isAutoVal_;
        const bool isPrimaryKey_;
        const bool notNull_;
    };
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[5]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(dirtyFlag_[1])
        {
            sql += "title,";
            ++parametersCount;
        }
        sql += "meta_title,";
        ++parametersCount;
        if(!dirtyFlag_[2])
        {
            needSelection=true;
        }
        if(dirtyFlag_[3])
        {
            sql += "slug,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "content,";
            ++parametersCount;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        sql +="default,";
        if(dirtyFlag_[1])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[2])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        else
        {
            sql +="default,";
        }
        if(dirtyFlag_[3])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(dirtyFlag_[4])
        {
            n = snprintf(placeholderStr,sizeof(placeholderStr),"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace blog
} // namespace drogon_model
