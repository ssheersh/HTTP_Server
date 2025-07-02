#pragma once
#include "socket.hpp"
#include <string>

class SocketConnector : public Socket {
public:
  void connect_to_host(const std::string &host, int port,
                       bool use_ipv6 = false);
};
