#include "socket.hpp"
#include "util/logger.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>

Socket::~Socket() { close_fd(); }

int Socket::get_fd() const { return fd; }

void Socket::set_fd(int new_fd) {
  std::cerr << "[set_fd] Setting fd = " << new_fd << "\n";
  if (fd >= 0)
    close(fd);
  fd = new_fd;
}

void Socket::close_fd() {
  if (fd >= 0) {
    close(fd);
    fd = -1;
  }
}

void Socket::create(int domain, int type, int protocol) {
  std::cerr << "[create] Calling socket()...\n";
  int new_fd = socket(domain, type, protocol);
  if (new_fd < 0) {
    throw std::runtime_error("socket creation failed");
  }
  std::cerr << "[create] Got socket FD: " << new_fd << "\n";
  set_fd(new_fd);
}
