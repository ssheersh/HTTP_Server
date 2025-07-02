
#include "server/http_server.hpp"

int main() {
  HttpServer server(8080, "./www");
  server.run();
  return 0;
}
