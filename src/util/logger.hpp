#pragma once
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

namespace Utils {

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
private:
  std::ofstream log_file;
  std::mutex log_mutex;
  bool enable_color;
  bool enable_console;

  std::string timestamp();
  std::string level_to_string(LogLevel level);
  std::string level_to_color(LogLevel level);

public:
  Logger(const std::string &log_path, bool color = true, bool console = true);
  ~Logger();

  void log(LogLevel level, const std::string &msg);

  void debug(const std::string &msg);
  void info(const std::string &msg);
  void warn(const std::string &msg);
  void error(const std::string &msg);
};

// 👇 Declare only (do NOT define here)
extern Logger global_logger;

} // namespace Utils

// Macros (same as before)
#define LOG_STREAM(LVL_FN, MSG)                                                \
  do {                                                                         \
    std::ostringstream oss__;                                                  \
    oss__ << MSG;                                                              \
    Utils::global_logger.LVL_FN(oss__.str());                                  \
  } while (0)

#define LOG_DEBUG(MSG) LOG_STREAM(debug, MSG)
#define LOG_INFO(MSG) LOG_STREAM(info, MSG)
#define LOG_WARN(MSG) LOG_STREAM(warn, MSG)
#define LOG_ERROR(MSG) LOG_STREAM(error, MSG)
