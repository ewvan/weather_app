#pragma once

#include <drogon/HttpSimpleController.h>
#include <drogon/drogon.h>
#include <nlohmann/json.hpp>
#include "services/weatherService/weather.h"


using namespace drogon;
using json = nlohmann::json;

class requestHandler : public drogon::HttpSimpleController<requestHandler, false>
{
  public:
  PATH_LIST_BEGIN
	PATH_ADD("/cities", Get);
  PATH_LIST_END
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;

};
