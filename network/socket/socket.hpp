#ifndef socket_hpp
#define socket_hpp

#include <arpa/inet.h>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace SOCK {
class Socket {
private:
  struct sockaddr_storage address;
  int sock;
  int connection;

public:
  Socket(int af = AF_INET, int service = SOCK_STREAM, int protocol = 0,
         uint16_t port = 8080,
         ulong interface = INADDR_ANY); // maybe unsafe if it ever asks for UDP
  virtual int connect_to_network(int sock, struct sockaddr_storage address) = 0;
  void test_connection(int);
  struct sockaddr_storage get_address();
  int get_sock();
  int get_connection();
  void set_connection(int);
};
} // namespace SOCK

#endif
