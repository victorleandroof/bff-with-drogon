#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class Login:public drogon::HttpController<Login>
{
  public:
    METHOD_LIST_BEGIN
      METHOD_ADD(Login::getIndex,"", Get);
    METHOD_LIST_END
    void getIndex(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
