#pragma once
#include <string>

struct HttpRequest {
  std::string method;
  std::string path;
  std::string version;

  static HttpRequest parse(const std::string &raw);
};
