#include "binder.hpp"
#include "socket.hpp"
#include <sys/socket.h>

SOCK::Binder::Binder(int af, int service, int protocol, int port,
                     ulong interface)
    : Socket(af, service, protocol, port, interface) {
  set_connection(connect_to_network(get_sock(), get_address()));
  test_connection(get_connection());
}

int SOCK::Binder::connect_to_network(int sock,
                                     struct sockaddr_storage address) {
  return bind(sock, (struct sockaddr *)&address, sizeof(address));
}
