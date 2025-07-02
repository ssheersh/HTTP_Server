#include "socket_binder.hpp"
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

void SocketBinder::bind_to_port(uint16_t port, bool use_ipv6) {
  int domain = use_ipv6 ? AF_INET6 : AF_INET;
  int server_fd = socket(domain, SOCK_STREAM, 0);
  if (server_fd < 0)
    throw std::runtime_error("Failed to create socket");

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if (use_ipv6) {
    sockaddr_in6 addr6{};
    addr6.sin6_family = AF_INET6;
    addr6.sin6_addr = in6addr_any;
    addr6.sin6_port = htons(port);
    if (bind(server_fd, (sockaddr *)&addr6, sizeof(addr6)) < 0)
      throw std::runtime_error("IPv6 bind failed");
  } else {
    sockaddr_in addr4{};
    addr4.sin_family = AF_INET;
    addr4.sin_addr.s_addr = INADDR_ANY;
    addr4.sin_port = htons(port);
    if (bind(server_fd, (sockaddr *)&addr4, sizeof(addr4)) < 0)
      throw std::runtime_error("IPv4 bind failed");
  }

  set_fd(server_fd);
}
