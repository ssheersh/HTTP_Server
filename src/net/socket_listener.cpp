#include "net/socket_listener.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

SocketListener::SocketListener(int port) {
  // Create an IPv6 socket (SOCK_STREAM = TCP)
  create(AF_INET6, SOCK_STREAM);
  bind_to_port(port); // optional: you can defer this if needed
}

void SocketListener::bind_to_port(int port) {
  int sockfd = get_fd();

  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    throw std::runtime_error("setsockopt failed");
  }

  struct sockaddr_in6 addr{};
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(port);
  addr.sin6_addr = in6addr_any; // this means "::" aka all IPv6 interfaces

  if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
    std::cerr << "bind failed: " << strerror(errno) << "\n";
    throw std::runtime_error("bind failed");
  }
}
void SocketListener::listen_on_port(int backlog) {
  if (listen(get_fd(), backlog) < 0) {
    throw std::runtime_error("listen failed");
  }
}

int SocketListener::accept_connection() {
  int client_fd = accept(get_fd(), nullptr, nullptr);
  if (client_fd < 0) {
    throw std::runtime_error("accept failed");
  }
  return client_fd;
}
