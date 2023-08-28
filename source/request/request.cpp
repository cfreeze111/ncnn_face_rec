#include "utils/utils.h"

#include <HTTPRequest.hpp>
#include <cjson/cJSON.h>
#include <glog/logging.h>

#include <string>
#include <vector>

#include "request.h"

namespace request {

std::string get(const std::string& url, std::string& params)
{
  LOG(INFO) << "Request URL: " << url;
  try {
    std::chrono::milliseconds timeout = std::chrono::milliseconds(5000);   // 5s
    http::Request             request(url);


    const auto response = request.send("GET", "params", {}, timeout);   // timeout=5

    std::string result = std::string(response.body.begin(), response.body.end());

    return result;
  }
  catch (const std::exception& e) {
    LOG(ERROR) << "Request failed, error message: " << e.what();

    return "";
  }
  LOG(INFO) << "=================================";
}

std::string post(const std::string& url, const cJSON* params)
{
  LOG(INFO) << "Request URL: " << url;
  try {
    std::chrono::milliseconds timeout = std::chrono::milliseconds(5000);   // 5s
    http::Request             request(url);

    const char* params_str = cJSON_Print(params);

    const auto response = request.send(
      "POST", std::string(params_str), {{"Content-Type", "application/json"}}, timeout);

    std::string result = std::string(response.body.begin(), response.body.end());

    return result;
  }
  catch (const std::exception& e) {
    LOG(ERROR) << "Request failed, error message: " << e.what();

    return "";
  }
  LOG(INFO) << "=================================";
}

}   // namespace request