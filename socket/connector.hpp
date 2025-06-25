#ifndef connector_h
#define connector_h

#include "socket.hpp"

namespace SOCK {
class Connector : public Socket {

public:
  Connector(int af, int service, int protocol, uint16_t port,
            ulong interface); // maybe unsafe if it ever asks for UDP
  int connect_to_network(int sock, struct sockaddr_storage address);
};
} // namespace SOCK

#endif
