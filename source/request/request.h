#include <cjson/cJSON.h>

#include <string>
#include <vector>

namespace request {

std::string get(const std::string& url, std::string& params);

std::string post(const std::string& url, const cJSON* params);

}   // namespace request