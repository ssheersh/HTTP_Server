#include "server/http_server.hpp"
#include <filesystem>
#include <iostream>

int main() {
  std::string root = std::filesystem::absolute("../static").string();
  HttpServer server(8080, root);
  server.run();
  return 0;
}
