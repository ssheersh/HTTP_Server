#include "socket.hpp"

Socket::~Socket() {
  if (fd >= 0)
    close(fd);
}

int Socket::get_fd() const { return fd; }

void Socket::set_fd(int new_fd) {
  if (fd >= 0)
    close(fd);
  fd = new_fd;
}

void Socket::close_fd() {
  if (fd >= 0)
    close(fd);
  fd = -1;
}

void Socket::create(int domain, int type, int protocol) {
  int new_fd = socket(domain, type, protocol);
  if (new_fd < 0) {
    throw std::runtime_error("socket creation failed");
  }
  set_fd(new_fd);
}
