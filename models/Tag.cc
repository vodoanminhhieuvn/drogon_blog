/**
 *
 *  Tag.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Tag.h"
#include "Post.h"
#include "PostTag.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

const std::string Tag::Cols::_id = "id";
const std::string Tag::Cols::_title = "title";
const std::string Tag::Cols::_meta_title = "meta_title";
const std::string Tag::Cols::_slug = "slug";
const std::string Tag::Cols::_content = "content";
const std::string Tag::primaryKeyName = "id";
const bool Tag::hasPrimaryKey = true;
const std::string Tag::tableName = "tag";

const std::vector<typename Tag::MetaData> Tag::metaData_={
{"id","int64_t","bigint",8,1,1,1},
{"title","std::string","character varying",75,0,0,1},
{"meta_title","std::string","character varying",100,0,0,0},
{"slug","std::string","character varying",100,0,0,1},
{"content","std::string","text",0,0,0,0}
};
const std::string &Tag::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Tag::Tag(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int64_t>(r["id"].as<int64_t>());
        }
        if(!r["title"].isNull())
        {
            title_=std::make_shared<std::string>(r["title"].as<std::string>());
        }
        if(!r["meta_title"].isNull())
        {
            metaTitle_=std::make_shared<std::string>(r["meta_title"].as<std::string>());
        }
        if(!r["slug"].isNull())
        {
            slug_=std::make_shared<std::string>(r["slug"].as<std::string>());
        }
        if(!r["content"].isNull())
        {
            content_=std::make_shared<std::string>(r["content"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            title_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            metaTitle_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            slug_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            content_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

Tag::Tag(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            title_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            metaTitle_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            slug_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
}

Tag::Tag(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("title"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["title"].isNull())
        {
            title_=std::make_shared<std::string>(pJson["title"].asString());
        }
    }
    if(pJson.isMember("meta_title"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["meta_title"].isNull())
        {
            metaTitle_=std::make_shared<std::string>(pJson["meta_title"].asString());
        }
    }
    if(pJson.isMember("slug"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["slug"].isNull())
        {
            slug_=std::make_shared<std::string>(pJson["slug"].asString());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
}

void Tag::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            title_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            metaTitle_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            slug_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
}

void Tag::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("title"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["title"].isNull())
        {
            title_=std::make_shared<std::string>(pJson["title"].asString());
        }
    }
    if(pJson.isMember("meta_title"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["meta_title"].isNull())
        {
            metaTitle_=std::make_shared<std::string>(pJson["meta_title"].asString());
        }
    }
    if(pJson.isMember("slug"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["slug"].isNull())
        {
            slug_=std::make_shared<std::string>(pJson["slug"].asString());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
}

const int64_t &Tag::getValueOfId() const noexcept
{
    const static int64_t defaultValue = int64_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &Tag::getId() const noexcept
{
    return id_;
}
void Tag::setId(const int64_t &pId) noexcept
{
    id_ = std::make_shared<int64_t>(pId);
    dirtyFlag_[0] = true;
}
const typename Tag::PrimaryKeyType & Tag::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const std::string &Tag::getValueOfTitle() const noexcept
{
    const static std::string defaultValue = std::string();
    if(title_)
        return *title_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Tag::getTitle() const noexcept
{
    return title_;
}
void Tag::setTitle(const std::string &pTitle) noexcept
{
    title_ = std::make_shared<std::string>(pTitle);
    dirtyFlag_[1] = true;
}
void Tag::setTitle(std::string &&pTitle) noexcept
{
    title_ = std::make_shared<std::string>(std::move(pTitle));
    dirtyFlag_[1] = true;
}

const std::string &Tag::getValueOfMetaTitle() const noexcept
{
    const static std::string defaultValue = std::string();
    if(metaTitle_)
        return *metaTitle_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Tag::getMetaTitle() const noexcept
{
    return metaTitle_;
}
void Tag::setMetaTitle(const std::string &pMetaTitle) noexcept
{
    metaTitle_ = std::make_shared<std::string>(pMetaTitle);
    dirtyFlag_[2] = true;
}
void Tag::setMetaTitle(std::string &&pMetaTitle) noexcept
{
    metaTitle_ = std::make_shared<std::string>(std::move(pMetaTitle));
    dirtyFlag_[2] = true;
}
void Tag::setMetaTitleToNull() noexcept
{
    metaTitle_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Tag::getValueOfSlug() const noexcept
{
    const static std::string defaultValue = std::string();
    if(slug_)
        return *slug_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Tag::getSlug() const noexcept
{
    return slug_;
}
void Tag::setSlug(const std::string &pSlug) noexcept
{
    slug_ = std::make_shared<std::string>(pSlug);
    dirtyFlag_[3] = true;
}
void Tag::setSlug(std::string &&pSlug) noexcept
{
    slug_ = std::make_shared<std::string>(std::move(pSlug));
    dirtyFlag_[3] = true;
}

const std::string &Tag::getValueOfContent() const noexcept
{
    const static std::string defaultValue = std::string();
    if(content_)
        return *content_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Tag::getContent() const noexcept
{
    return content_;
}
void Tag::setContent(const std::string &pContent) noexcept
{
    content_ = std::make_shared<std::string>(pContent);
    dirtyFlag_[4] = true;
}
void Tag::setContent(std::string &&pContent) noexcept
{
    content_ = std::make_shared<std::string>(std::move(pContent));
    dirtyFlag_[4] = true;
}
void Tag::setContentToNull() noexcept
{
    content_.reset();
    dirtyFlag_[4] = true;
}

void Tag::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Tag::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "title",
        "meta_title",
        "slug",
        "content"
    };
    return inCols;
}

void Tag::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTitle())
        {
            binder << getValueOfTitle();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getMetaTitle())
        {
            binder << getValueOfMetaTitle();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSlug())
        {
            binder << getValueOfSlug();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Tag::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    return ret;
}

void Tag::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getTitle())
        {
            binder << getValueOfTitle();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getMetaTitle())
        {
            binder << getValueOfMetaTitle();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getSlug())
        {
            binder << getValueOfSlug();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getContent())
        {
            binder << getValueOfContent();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Tag::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=(Json::Int64)getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getMetaTitle())
    {
        ret["meta_title"]=getValueOfMetaTitle();
    }
    else
    {
        ret["meta_title"]=Json::Value();
    }
    if(getSlug())
    {
        ret["slug"]=getValueOfSlug();
    }
    else
    {
        ret["slug"]=Json::Value();
    }
    if(getContent())
    {
        ret["content"]=getValueOfContent();
    }
    else
    {
        ret["content"]=Json::Value();
    }
    return ret;
}

Json::Value Tag::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=(Json::Int64)getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getTitle())
            {
                ret[pMasqueradingVector[1]]=getValueOfTitle();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getMetaTitle())
            {
                ret[pMasqueradingVector[2]]=getValueOfMetaTitle();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getSlug())
            {
                ret[pMasqueradingVector[3]]=getValueOfSlug();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getContent())
            {
                ret[pMasqueradingVector[4]]=getValueOfContent();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=(Json::Int64)getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getMetaTitle())
    {
        ret["meta_title"]=getValueOfMetaTitle();
    }
    else
    {
        ret["meta_title"]=Json::Value();
    }
    if(getSlug())
    {
        ret["slug"]=getValueOfSlug();
    }
    else
    {
        ret["slug"]=Json::Value();
    }
    if(getContent())
    {
        ret["content"]=getValueOfContent();
    }
    else
    {
        ret["content"]=Json::Value();
    }
    return ret;
}

bool Tag::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(1, "title", pJson["title"], err, true))
            return false;
    }
    else
    {
        err="The title column cannot be null";
        return false;
    }
    if(pJson.isMember("meta_title"))
    {
        if(!validJsonOfField(2, "meta_title", pJson["meta_title"], err, true))
            return false;
    }
    if(pJson.isMember("slug"))
    {
        if(!validJsonOfField(3, "slug", pJson["slug"], err, true))
            return false;
    }
    else
    {
        err="The slug column cannot be null";
        return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(4, "content", pJson["content"], err, true))
            return false;
    }
    return true;
}
bool Tag::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                             const std::vector<std::string> &pMasqueradingVector,
                                             std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
            return false;
        }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Tag::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(1, "title", pJson["title"], err, false))
            return false;
    }
    if(pJson.isMember("meta_title"))
    {
        if(!validJsonOfField(2, "meta_title", pJson["meta_title"], err, false))
            return false;
    }
    if(pJson.isMember("slug"))
    {
        if(!validJsonOfField(3, "slug", pJson["slug"], err, false))
            return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(4, "content", pJson["content"], err, false))
            return false;
    }
    return true;
}
bool Tag::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                           const std::vector<std::string> &pMasqueradingVector,
                                           std::string &err)
{
    if(pMasqueradingVector.size() != 5)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Tag::validJsonOfField(size_t index,
                           const std::string &fieldName,
                           const Json::Value &pJson,
                           std::string &err,
                           bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }
            if(!pJson.isInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 75)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 75)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 100)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 100)";
                return false;
            }

            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 100)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 100)";
                return false;
            }

            break;
        case 4:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
std::vector<std::pair<Post,PostTag>> Tag::getPosts(const drogon::orm::DbClientPtr &clientPtr) const {
    std::shared_ptr<std::promise<std::vector<std::pair<Post,PostTag>>>> pro(new std::promise<std::vector<std::pair<Post,PostTag>>>);
    std::future<std::vector<std::pair<Post,PostTag>>> f = pro->get_future();
    getPosts(clientPtr, [&pro] (std::vector<std::pair<Post,PostTag>> result) {
        try {
            pro->set_value(result);
        }
        catch (...) {
            pro->set_exception(std::current_exception());
        }
    }, [&pro] (const DrogonDbException &err) {
        pro->set_exception(std::make_exception_ptr(err));
    });
    return f.get();
}
void Tag::getPosts(const DbClientPtr &clientPtr,
                   const std::function<void(std::vector<std::pair<Post,PostTag>>)> &rcb,
                   const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from post,post_tag where post_tag.tag_id = $1 and post_tag.post_id = post.id";
    *clientPtr << sql
               << *id_
               >> [rcb = std::move(rcb)](const Result &r){
                   std::vector<std::pair<Post,PostTag>> ret;
                   ret.reserve(r.size());
                   for (auto const &row : r)
                   {
                       ret.emplace_back(std::pair<Post,PostTag>(
                           Post(row),PostTag(row,Post::getColumnNumber())));
                   }
                   rcb(ret);
               }
               >> ecb;
}
