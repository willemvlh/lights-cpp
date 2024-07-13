#include "TimingFunction.h"

int Linear::operator()(int step, int) const {
  return step;
};

int EaseIn::operator()(int step, int totalSteps) const {
    float ratio = static_cast<float>(step) / totalSteps;
    float exp = ratio * ratio;
    return std::round(exp * totalSteps);
  }

int EaseOut::operator()(int step, int totalSteps) const {
    float ratio = static_cast<float>(step) / totalSteps;
    float exp = std::pow(ratio, 0.5);
    return std::round(exp * totalSteps);
}
