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
