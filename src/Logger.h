#pragma once
#include <iomanip>
#include <iostream>
#include <mutex>
#include <ostream>
#include <string>
#include <chrono>

enum LogLevel { Error, Info, Debug };

class Logger {
private:
  std::mutex mutex;
  LogLevel level;
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }
  void _log(const std::string msg, LogLevel level) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::lock_guard<std::mutex> lock(mutex);
    if (level <= this->level) {
      std::cerr << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "  " << msg << std::endl;
    }
  };

public:
  static void setLevel(LogLevel level) { getInstance().level = level; }
  static void log(const std::string msg, LogLevel level) {
    getInstance()._log(msg, level);
  };
};

void log(const std::string, LogLevel);
