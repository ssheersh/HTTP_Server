#include "socket_connector.hpp"
#include <cstring>
#include <netdb.h>
#include <stdexcept>
#include <unistd.h>

void SocketConnector::connect_to_host(const std::string &host, int port,
                                      bool use_ipv6) {
  struct addrinfo hints{}, *res = nullptr;

  hints.ai_family = use_ipv6 ? AF_INET6 : AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int status =
      getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
  if (status != 0)
    throw std::runtime_error("getaddrinfo: " +
                             std::string(gai_strerror(status)));

  int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) {
    freeaddrinfo(res);
    throw std::runtime_error("Failed to create client socket");
  }

  if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
    close(sockfd);
    freeaddrinfo(res);
    throw std::runtime_error("Connection failed");
  }

  freeaddrinfo(res);
  set_fd(sockfd);
}
