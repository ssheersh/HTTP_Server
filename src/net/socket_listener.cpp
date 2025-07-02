
#include "socket_listener.hpp"
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

void SocketListener::listen_for_connections(int backlog) {
  if (listen(get_fd(), backlog) < 0)
    throw std::runtime_error("listen failed");
}

int SocketListener::accept_connection() {
  int client_fd = accept(get_fd(), nullptr, nullptr);
  if (client_fd < 0)
    throw std::runtime_error("accept failed");
  return client_fd;
}
