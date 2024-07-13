#include <cmath>
namespace Utility {
void waitFor(int milliseconds);
float wrapHue(float hue);
char* readEnv(const char* envVar, const char* _default);
float rand_between(float min, float max);
} // namespace Utility
