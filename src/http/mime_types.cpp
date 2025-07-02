#include "mime_types.hpp"
#include <unordered_map>

std::string mime_type_from_extension(const std::string &path) {
  static const std::unordered_map<std::string, std::string> types{
      {".html", "text/html"},
      {".css", "text/css"},
      {".js", "application/javascript"},
      {".png", "image/png"},
      {".jpg", "image/jpeg"},
      {".txt", "text/plain"}};

  auto dot = path.find_last_of('.');
  if (dot == std::string::npos)
    return "application/octet-stream";

  auto ext = path.substr(dot);
  auto it = types.find(ext);
  return it != types.end() ? it->second : "application/octet-stream";
}
