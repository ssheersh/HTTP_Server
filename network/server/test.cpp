#include "test.hpp"
#include <cstddef>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

SOCK::Test::Test() : Server(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
  launch();
}

void SOCK::Test::acceptor() {
  struct sockaddr_storage address;
  int ad_len = sizeof(address);
  new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address,
                      (socklen_t *)&ad_len);
  read(new_socket, buffer, sizeof(buffer));
}

void SOCK::Test::handler() { std::cout << buffer << "\n"; }

void SOCK::Test::responder() {
  std::string hello = "Hello World";
  write(new_socket, hello.c_str(), (size_t)hello.size());
  close(new_socket);
}

void SOCK::Test::launch() {
  while (1) {
    std::cout << "===Waiting===\n";
    acceptor();
    handler();
    responder();
    std::cout << "DONE\n";
  }
}
