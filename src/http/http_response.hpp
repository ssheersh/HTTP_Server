#pragma once
#include "http_request.hpp"
#include <string>

class HttpResponse {
public:
  static std::string build(const std::string &root, const HttpRequest &req);
};
