#pragma once
#include "http/http_request.hpp"
#include "net/socket_listener.hpp"
#include <string>

class HttpServer {
  SocketListener listener;
  int port;
  std::string root_dir;

public:
  HttpServer(int port, const std::string &root);
  void run();
};
