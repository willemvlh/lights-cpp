#pragma once

#include <cmath>
#include <cstdio>
class TimingFunction {
public:
  virtual int operator()(int step, int totalSteps) const = 0;
};

class EaseIn: public TimingFunction {
public:
  int operator()(int step, int totalSteps) const override;
};

class EaseOut: public TimingFunction {
public:
  int operator()(int step, int totalSteps) const override;
};

class Linear : public TimingFunction {
public:
  int operator()(int step, int totalSteps) const override;
};
