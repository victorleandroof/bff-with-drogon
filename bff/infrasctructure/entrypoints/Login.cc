#include "Login.h"
#include <json/json.h>
#include <fstream>

std::vector<std::vector<std::string>> assetsCached;

std::vector<std::vector<std::string>> getAssetsUrl()
{
  if(!assetsCached.empty()){
    LOG_DEBUG << "(HomeController) - get assets from cache";
    return assetsCached;
  }
  std::ifstream json_file("../assets.json", std::ifstream::binary);
  Json::Value assets;
  json_file >> assets;
  std::vector<std::string> jsUrls;
  std::vector<std::string> cssUrls; 
  for(auto asset: assets){
    std::string urlJs = asset["js"].asString();
    std::string urlCss = asset["css"].asString();
    if(!urlCss.empty()) {
      cssUrls.push_back(urlCss);
    } 
    if(!urlJs.empty()) {
      jsUrls.push_back(urlJs);
    }
  }
  assetsCached = {jsUrls, cssUrls};
  return assetsCached;
}

void Login::getIndex(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
  LOG_DEBUG<<"(HomeController) - GET INDEX";
 
  auto assetsUrl = getAssetsUrl();
  
  std::vector<std::string> js = assetsUrl[0];
  std::vector<std::string> css = assetsUrl[1];
  
  HttpViewData data;
  data.insert("baseUrl", "/login");
  data.insert("css", css);
  data.insert("js", js);

  auto resp = HttpResponse::newHttpViewResponse("Index.csp", data);
  
  callback(resp);

}




