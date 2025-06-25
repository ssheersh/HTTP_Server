#ifndef test_hpp
#define test_hpp

#include "server.hpp"

namespace SOCK {
class Test : public Server {
private:
  char buffer[30000] = {0};
  int new_socket;

public:
  Test();
  void launch() override;
  void acceptor();
  void handler() override;
  void responder() override;
};
} // namespace SOCK

#endif
