#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

void send_request(const std::string &host, const std::string &port,
                  const std::string &path) {
  struct addrinfo hints{}, *res;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0) {
    perror("getaddrinfo");
    return;
  }

  int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock < 0) {
    perror("socket");
    return;
  }

  if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
    perror("connect");
    close(sock);
    return;
  }

  std::string req = "GET " + path + " HTTP/1.1\r\nHost: " + host +
                    "\r\nConnection: close\r\n\r\n";
  send(sock, req.c_str(), req.length(), 0);

  char buffer[4096];
  ssize_t len;
  while ((len = read(sock, buffer, sizeof(buffer))) > 0) {
    std::cout << std::string(buffer, len);
  }

  close(sock);
  freeaddrinfo(res);
}

int main() {
  send_request("localhost", "8080", "/");
  return 0;
}
