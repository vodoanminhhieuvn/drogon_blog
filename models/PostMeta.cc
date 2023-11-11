/**
 *
 *  PostMeta.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "PostMeta.h"
#include "Post.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::blog;

const std::string PostMeta::Cols::_id = "id";
const std::string PostMeta::Cols::_post_id = "post_id";
const std::string PostMeta::Cols::_content = "content";
const std::string PostMeta::primaryKeyName = "id";
const bool PostMeta::hasPrimaryKey = true;
const std::string PostMeta::tableName = "post_meta";

const std::vector<typename PostMeta::MetaData> PostMeta::metaData_={
{"id","int64_t","bigint",8,1,1,1},
{"post_id","int64_t","bigint",8,0,0,1},
{"content","std::string","text",0,0,0,0}
};
const std::string &PostMeta::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
PostMeta::PostMeta(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            id_=std::make_shared<int64_t>(r["id"].as<int64_t>());
        }
        if(!r["post_id"].isNull())
        {
            postId_=std::make_shared<int64_t>(r["post_id"].as<int64_t>());
        }
        if(!r["content"].isNull())
        {
            content_=std::make_shared<std::string>(r["content"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
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
            postId_=std::make_shared<int64_t>(r[index].as<int64_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            content_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

PostMeta::PostMeta(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
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
            postId_=std::make_shared<int64_t>((int64_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
}

PostMeta::PostMeta(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("post_id"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["post_id"].isNull())
        {
            postId_=std::make_shared<int64_t>((int64_t)pJson["post_id"].asInt64());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
}

void PostMeta::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
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
            postId_=std::make_shared<int64_t>((int64_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            content_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
}

void PostMeta::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<int64_t>((int64_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("post_id"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["post_id"].isNull())
        {
            postId_=std::make_shared<int64_t>((int64_t)pJson["post_id"].asInt64());
        }
    }
    if(pJson.isMember("content"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["content"].isNull())
        {
            content_=std::make_shared<std::string>(pJson["content"].asString());
        }
    }
}

const int64_t &PostMeta::getValueOfId() const noexcept
{
    const static int64_t defaultValue = int64_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &PostMeta::getId() const noexcept
{
    return id_;
}
void PostMeta::setId(const int64_t &pId) noexcept
{
    id_ = std::make_shared<int64_t>(pId);
    dirtyFlag_[0] = true;
}
const typename PostMeta::PrimaryKeyType & PostMeta::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

const int64_t &PostMeta::getValueOfPostId() const noexcept
{
    const static int64_t defaultValue = int64_t();
    if(postId_)
        return *postId_;
    return defaultValue;
}
const std::shared_ptr<int64_t> &PostMeta::getPostId() const noexcept
{
    return postId_;
}
void PostMeta::setPostId(const int64_t &pPostId) noexcept
{
    postId_ = std::make_shared<int64_t>(pPostId);
    dirtyFlag_[1] = true;
}

const std::string &PostMeta::getValueOfContent() const noexcept
{
    const static std::string defaultValue = std::string();
    if(content_)
        return *content_;
    return defaultValue;
}
const std::shared_ptr<std::string> &PostMeta::getContent() const noexcept
{
    return content_;
}
void PostMeta::setContent(const std::string &pContent) noexcept
{
    content_ = std::make_shared<std::string>(pContent);
    dirtyFlag_[2] = true;
}
void PostMeta::setContent(std::string &&pContent) noexcept
{
    content_ = std::make_shared<std::string>(std::move(pContent));
    dirtyFlag_[2] = true;
}
void PostMeta::setContentToNull() noexcept
{
    content_.reset();
    dirtyFlag_[2] = true;
}

void PostMeta::updateId(const uint64_t id)
{
}

const std::vector<std::string> &PostMeta::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "post_id",
        "content"
    };
    return inCols;
}

void PostMeta::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getPostId())
        {
            binder << getValueOfPostId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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

const std::vector<std::string> PostMeta::updateColumns() const
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
    return ret;
}

void PostMeta::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[1])
    {
        if(getPostId())
        {
            binder << getValueOfPostId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
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
Json::Value PostMeta::toJson() const
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
    if(getPostId())
    {
        ret["post_id"]=(Json::Int64)getValueOfPostId();
    }
    else
    {
        ret["post_id"]=Json::Value();
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

Json::Value PostMeta::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
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
            if(getPostId())
            {
                ret[pMasqueradingVector[1]]=(Json::Int64)getValueOfPostId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getContent())
            {
                ret[pMasqueradingVector[2]]=getValueOfContent();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
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
    if(getPostId())
    {
        ret["post_id"]=(Json::Int64)getValueOfPostId();
    }
    else
    {
        ret["post_id"]=Json::Value();
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

bool PostMeta::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("post_id"))
    {
        if(!validJsonOfField(1, "post_id", pJson["post_id"], err, true))
            return false;
    }
    else
    {
        err="The post_id column cannot be null";
        return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(2, "content", pJson["content"], err, true))
            return false;
    }
    return true;
}
bool PostMeta::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                  const std::vector<std::string> &pMasqueradingVector,
                                                  std::string &err)
{
    if(pMasqueradingVector.size() != 3)
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
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool PostMeta::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("post_id"))
    {
        if(!validJsonOfField(1, "post_id", pJson["post_id"], err, false))
            return false;
    }
    if(pJson.isMember("content"))
    {
        if(!validJsonOfField(2, "content", pJson["content"], err, false))
            return false;
    }
    return true;
}
bool PostMeta::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 3)
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
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool PostMeta::validJsonOfField(size_t index,
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
            if(!pJson.isInt64())
            {
                err="Type error in the "+fieldName+" field";
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
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}

Post PostMeta::getPost(const drogon::orm::DbClientPtr &clientPtr) const {
    std::shared_ptr<std::promise<Post>> pro(new std::promise<Post>);
    std::future<Post> f = pro->get_future();
    getPost(clientPtr, [&pro] (Post result) {
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
void PostMeta::getPost(const DbClientPtr &clientPtr,
                       const std::function<void(Post)> &rcb,
                       const ExceptionCallback &ecb) const
{
    const static std::string sql = "select * from post where id = $1";
    *clientPtr << sql
               << *postId_
               >> [rcb = std::move(rcb), ecb](const Result &r){
                    if (r.size() == 0)
                    {
                        ecb(UnexpectedRows("0 rows found"));
                    }
                    else if (r.size() > 1)
                    {
                        ecb(UnexpectedRows("Found more than one row"));
                    }
                    else
                    {
                        rcb(Post(r[0]));
                    }
               }
               >> ecb;
}