#include "socket_binder.hpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>

void SocketBinder::bind_to_port(uint16_t port, bool use_ipv6) {
  const int domain = use_ipv6 ? AF_INET6 : AF_INET;
  int server_fd = get_fd();
  if (server_fd < 0) {
    throw std::runtime_error("socket() failed");
  }

  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    close(server_fd);
    throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
  }

  if (use_ipv6) {
    int off = 0; // allow dual-stack
    if (setsockopt(server_fd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off)) <
        0) {
      close(server_fd);
      throw std::runtime_error("setsockopt(IPV6_V6ONLY) failed");
    }

    sockaddr_in6 addr6{};
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    addr6.sin6_addr = in6addr_any;

    if (bind(server_fd, reinterpret_cast<sockaddr *>(&addr6), sizeof(addr6)) <
        0) {
      close(server_fd);
      throw std::runtime_error("bind(AF_INET6) failed");
    }
  } else {
    sockaddr_in addr4{};
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);
    addr4.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, reinterpret_cast<sockaddr *>(&addr4), sizeof(addr4)) <
        0) {
      close(server_fd);
      throw std::runtime_error("bind(AF_INET) failed");
    }
  }

  set_fd(server_fd);
}
