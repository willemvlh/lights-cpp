#include <cmath>

#define ASSERT_MSG(condition, msg) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: (" #condition "), " \
                      << "function " << __FUNCTION__ << ", " \
                      << "file " << __FILE__ << ", " \
                      << "line " << __LINE__ << ": " << msg << std::endl; \
            std::abort(); \
        } \
    } while (false)


namespace Utility {
void waitFor(int milliseconds);
float wrapHue(float hue);
char* readEnv(const char* envVar, const char* _default);
float rand_between(float min, float max);
} // namespace Utility
