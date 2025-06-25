#include "listener.hpp"
#include <sys/types.h>

SOCK::Listener::Listener(int af, int service, int protocol, u_int16_t port,
                         u_long interface, int bklog)
    : Binder(af, service, protocol, port, interface) {
  backlog = bklog;
}

void SOCK::Listener::start_listening() {
  listening = listen(get_connection(), backlog);
}
