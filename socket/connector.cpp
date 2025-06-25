#include "connector.hpp"
#include <sys/types.h>

SOCK::Connector::Connector(int af, int service, int protocol, u_int16_t port,
                           ulong interface)
    : Socket(af, service, protocol, port, interface) {
  set_connection(connect_to_network(get_sock(), get_address()));
  test_connection(get_connection());
}

int SOCK::Connector::connect_to_network(int sock,
                                        struct sockaddr_storage address) {
  return connect(sock, (struct sockaddr *)&address, sizeof(address));
}
