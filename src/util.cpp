#include <chrono>
#include <thread>
namespace Utility {
void waitFor(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
} // namespace Utility
