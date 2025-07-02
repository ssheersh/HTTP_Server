
#pragma once

#include "net/socket.hpp"

class SocketListener : public Socket {
public:
  SocketListener(int port);

  void bind_to_port(int port);
  void listen_on_port(int backlog = 10);
  int accept_connection();
};
