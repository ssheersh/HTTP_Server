#pragma once
#include "socket.hpp"
#include <cstdint>

class SocketBinder : public Socket {
public:
  void bind_to_port(uint16_t port, bool use_ipv6 = false);
};
