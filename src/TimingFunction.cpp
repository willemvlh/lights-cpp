#include "TimingFunction.h"

float Linear::operator()(float t) const { return t; };

float EaseIn::operator()(float t) const { return t * t; }

float EaseOut::operator()(float t) const {
  return 1.0f - (1.0f - t) * (1.0f - t);
}

float EaseInOut::operator()(float t) const {
  return t < 0.5f ? 2.0f * t * t : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
}
