#include "util/logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Utils {

// ✅ Define it once and only here
Logger global_logger("server.log", true, true);

Logger::Logger(const std::string &path, bool color, bool console)
    : enable_color(color), enable_console(console) {
  log_file.open(path, std::ios::app);
  if (!log_file.is_open()) {
    std::cerr << "[Logger] Could not open log file: " << path << std::endl;
  }
}

Logger::~Logger() {
  if (log_file.is_open()) {
    log_file.close();
  }
}

std::string Logger::timestamp() {
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::ostringstream oss;
  oss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
  return oss.str();
}

std::string Logger::level_to_string(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO ";
  case LogLevel::WARN:
    return "WARN ";
  case LogLevel::ERROR:
    return "ERROR";
  }
  return "UNKWN";
}

std::string Logger::level_to_color(LogLevel level) {
  if (!enable_color)
    return "";

  switch (level) {
  case LogLevel::DEBUG:
    return "\033[36m"; // Cyan
  case LogLevel::INFO:
    return "\033[32m"; // Green
  case LogLevel::WARN:
    return "\033[33m"; // Yellow
  case LogLevel::ERROR:
    return "\033[31m"; // Red
  }
  return "";
}

void Logger::log(LogLevel level, const std::string &msg) {
  std::lock_guard<std::mutex> lock(log_mutex);
  std::string time = timestamp();
  std::string label = level_to_string(level);
  std::string line = "[" + time + "] [" + label + "] " + msg;

  if (enable_console) {
    std::string color = level_to_color(level);
    std::string reset = enable_color ? "\033[0m" : "";
    std::cerr << color << line << reset << std::endl;
  }

  if (log_file.is_open()) {
    log_file << line << std::endl;
  }
}

void Logger::debug(const std::string &msg) { log(LogLevel::DEBUG, msg); }
void Logger::info(const std::string &msg) { log(LogLevel::INFO, msg); }
void Logger::warn(const std::string &msg) { log(LogLevel::WARN, msg); }
void Logger::error(const std::string &msg) { log(LogLevel::ERROR, msg); }

} // namespace Utils
