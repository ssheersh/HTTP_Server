#include "http_request.hpp"
#include <sstream>

HttpRequest HttpRequest::parse(const std::string &raw) {
  std::istringstream stream(raw);
  HttpRequest req;
  stream >> req.method >> req.path >> req.version;
  return req;
}
