#include "socket.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

SOCK::Socket::Socket(int af, int service, int protocol, uint16_t port,
                     ulong interface)
    : sock(-1) {

  std::memset(&address, 0, sizeof(address));
  if (af == AF_INET) {
    auto *addr4 = reinterpret_cast<sockaddr_in *>(&address);
    addr4->sin_family = AF_INET;
    addr4->sin_port = htons(port);
    addr4->sin_addr.s_addr = htonl(INADDR_ANY);
  }

  else if (af == AF_INET6) {
    auto *addr6 = reinterpret_cast<sockaddr_in6 *>(&address);
    addr6->sin6_family = AF_INET6;
    addr6->sin6_port = htons(port);
    addr6->sin6_addr = in6addr_any;
  } else {
    ::close(sock);
    throw std::runtime_error("Unsupported address family");
  }
  sock = socket(af, service, protocol);
  test_connection(sock);
}

void SOCK::Socket::test_connection(int test) {
  if (test < 0) {
    perror("Failed to connect");
    exit(EXIT_FAILURE);
  }
}

struct sockaddr_storage SOCK::Socket::get_address() { return address; }
int SOCK::Socket::get_sock() { return sock; }
int SOCK::Socket::get_connection() { return connection; }

void SOCK::Socket::set_connection(int conn) { connection = conn; }
