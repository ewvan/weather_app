#include "requestHandler.h"

void requestHandler::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
  auto cities = req->getParameters();

  json allData = json::array();

  json body = {};
  for (auto city : cities) {
	allData.push_back({
	  city.second,
	  getWeatherData(city.second)}
	);
  }
  body["data"] = allData;

  auto resp = HttpResponse::newHttpResponse();
  resp->setStatusCode(k200OK);
  resp->addHeader("Access-Control-Allow-Origin", "*");
  resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
  resp->addHeader("Access-Control-Allow-Headers", "*");
  resp->addHeader("Access-Control-Allow-Credentials", "true");
  resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
  resp->setBody(body.dump());

  callback(resp);
}
