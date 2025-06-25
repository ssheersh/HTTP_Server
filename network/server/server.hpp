#ifndef server_hpp
#define server_hpp

#include "../lib_networks.hpp"
#include <stdio.h>
#include <sys/types.h>

namespace SOCK {
class Server {
private:
  Listener *socket;
  virtual void accepter() = 0;
  virtual void handler() = 0;
  virtual void responder() = 0;

public:
  Server(int af, int service, int protocol, u_int16_t port, u_long interface,
         int bklog);
  virtual void launch() = 0; // for loop in child class;
  Listener *get_socket();
};
} // namespace SOCK
#endif
