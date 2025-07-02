#pragma once
#include "socket.hpp"

class SocketListener : public Socket {
public:
  void listen_for_connections(int backlog = 10);
  int accept_connection();
};
