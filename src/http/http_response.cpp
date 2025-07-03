#include "http_response.hpp"
#include "mime_types.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

std::string HttpResponse::build(const std::string &root,
                                const HttpRequest &req) {
  if (req.method != "GET")
    return "HTTP/1.1 405 Method Not Allowed\r\n\r\nMethod Not Allowed";

  std::string path = req.path == "/" ? "/index.html" : req.path;
  std::string full_path = root + path;

  std::cerr << "[DEBUG] Full path: " << full_path << std::endl;
  if (!std::filesystem::exists(full_path) ||
      std::filesystem::is_directory(full_path))
    return "HTTP/1.1 404 Not Found\r\n\r\nFile Not Found";

  std::ifstream file(full_path, std::ios::binary);
  std::ostringstream content;
  content << file.rdbuf();
  std::string body = content.str();
  std::string mime = mime_type_from_extension(full_path);

  std::ostringstream response;
  response << "HTTP/1.1 200 OK\r\n"
           << "Content-Type: " << mime << "\r\n"
           << "Content-Length: " << body.size() << "\r\n\r\n"
           << body;

  return response.str();
}
