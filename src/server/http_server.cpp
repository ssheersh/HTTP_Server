#include "server/http_server.hpp"
#include "http/http_response.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

HttpServer::HttpServer(int port, const std::string &root)
    : port(port), root_dir(root), listener(port) {}

void HttpServer::run() {
  listener.bind_to_port(port);
  listener.listen_on_port();

  std::cout << "Server listening on http://localhost:" << port << std::endl;

  while (true) {
    int client_fd = listener.accept_connection();
    if (client_fd < 0)
      continue;

    char buffer[4096];
    ssize_t len = read(client_fd, buffer, sizeof(buffer));
    if (len <= 0) {
      close(client_fd);
      continue;
    }

    std::string request_str(buffer, len);
    HttpRequest req = HttpRequest::parse(request_str);
    std::string response = HttpResponse::build(root_dir, req);

    send(client_fd, response.c_str(), response.size(), 0);
    close(client_fd);
  }
}
