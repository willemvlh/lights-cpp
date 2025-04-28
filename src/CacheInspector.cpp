#include "CacheInspector.h"
#include "Logger.h"
#include <thread>

const void CacheInspector::report() {
  while (1) {
    Logger::log("Cache items: " + std::to_string(cache.size()), Debug);
    Logger::log("Current size: " + std::to_string(cache.sizeBytes() / 1024) + " KB",
                Debug);
    std::this_thread::sleep_for(std::chrono::seconds(120));
  }
}
