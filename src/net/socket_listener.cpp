#include "socket_listener.hpp"
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

SocketListener::SocketListener(int port) {
  create(AF_INET6, SOCK_STREAM, 0);
  std::cerr << "[SocketListener] FD after create: " << get_fd() << "\n";
  bind_to_port(port);
}

void SocketListener::bind_to_port(int port) {
  int sockfd = get_fd();

  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
  }

  int off = 0; // enable dual-stack
  if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off)) < 0) {
    std::cerr << "From listener\n";
    std::cerr << sockfd << "\n";
    std::cerr << setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &off,
                            sizeof(off))
              << "\n";
    throw std::runtime_error("setsockopt(IPV6_V6ONLY) failed");
  }

  sockaddr_in6 addr{};
  addr.sin6_family = AF_INET6;
  addr.sin6_port = htons(port);
  addr.sin6_addr = in6addr_any;

  if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
    std::cerr << "bind failed: " << strerror(errno) << "\n";
    throw std::runtime_error("bind(AF_INET6) failed");
  }
}

void SocketListener::listen_on_port(int backlog) {
  if (listen(get_fd(), backlog) < 0) {
    throw std::runtime_error("listen() failed");
  }
}

int SocketListener::accept_connection() {
  int client_fd = accept(get_fd(), nullptr, nullptr);
  if (client_fd < 0) {
    throw std::runtime_error("accept() failed");
  }
  return client_fd;
}
