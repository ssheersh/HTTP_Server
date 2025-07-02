#pragma once
#include <stdexcept>
#include <unistd.h>

class Socket {
protected:
  int fd = -1;

public:
  Socket() = default;
  virtual ~Socket();

  int get_fd() const;
  void set_fd(int new_fd);
  void close_fd();
};
