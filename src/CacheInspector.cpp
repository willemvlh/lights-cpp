#include "CacheInspector.h"
#include "Logger.h"
#include <thread>

const void CacheInspector::report() {
  while (1) {
    Logger::log("__Cache items__: " + std::to_string(cache.size()), Debug);
    Logger::log("__Current size__: " + std::to_string(cache.sizeBytes()),
                Debug);
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
}
