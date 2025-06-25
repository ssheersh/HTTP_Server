#ifndef listener_h
#define listener_h
#include "binder.hpp"
#include <stdio.h>
#include <sys/types.h>
namespace SOCK {
class Listener : public Binder {
private:
  int backlog;
  int listening;

public:
  Listener(int af, int service, int protocol, uint16_t port, ulong interface,
           int bklog);
  void start_listening();
};
} // namespace SOCK
#endif
