#include "server.hpp"
#include <sys/types.h>

SOCK::Server::Server(int af, int service, int protocol, u_int16_t port,
                     u_long interface, int bklog) {
  socket = new Listener(af, service, protocol, port, interface, bklog);
}

SOCK::Listener *SOCK::Server::get_socket() { return socket; }
