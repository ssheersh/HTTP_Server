#ifndef binder_hpp
#define binder_hpp

#include "socket.hpp"
#include <stdio.h>
#include <sys/socket.h>

namespace SOCK {
class Binder : public Socket {
public:
  Binder(int af, int service, int protocol, int port, ulong interface);
  int connect_to_network(int sock, struct sockaddr_storage address) override;
};
} // namespace SOCK

#endif
