#pragma once
#include <fstream>
#include <mutex>
#include <string>

namespace Utils {
class Logger {
private:
  std::string log_path;
  std::ofstream log_file;
  std::mutex log_mutex;

public:
  Logger(const std::string &path);
  ~Logger();

  void log(const std::string &msg);
};
} // namespace Utils
