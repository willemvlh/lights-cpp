#include "TimingFunction.h"

int Linear::operator()(int step, int) const {
  return step;
};

int EaseIn::operator()(int step, int totalSteps) const {
    float ratio = static_cast<float>(step) / totalSteps;
    float exp = ratio * ratio;
    return std::round(exp * totalSteps);
  }

