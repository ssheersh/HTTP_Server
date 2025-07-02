#include "util/logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Utils {

Logger::Logger(const std::string &path) : log_path(path) {
  log_file.open(log_path, std::ios::app);
  if (!log_file.is_open()) {
    std::cerr << "Logger error: failed to open log file at " << path
              << std::endl;
  }
}

Logger::~Logger() {
  if (log_file.is_open()) {
    log_file.close();
  }
}

void Logger::log(const std::string &msg) {
  if (!log_file.is_open())
    return;

  std::lock_guard<std::mutex> guard(log_mutex);

  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  log_file << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
           << "] " << msg << std::endl;
}
} // namespace Utils
