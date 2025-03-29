#pragma once

#include <cmath>
#include <cstdio>
class TimingFunction {
public:
  virtual int operator()(int step, int totalSteps) const = 0;
};

class EaseIn : public TimingFunction {
private:
  double factor;

public:
  EaseIn(double factor) : TimingFunction(), factor(factor) {};
  int operator()(int step, int totalSteps) const override;
};

class EaseOut : public TimingFunction {
private:
  double factor;

public:
  EaseOut(double factor) : factor(factor) {};
  int operator()(int step, int totalSteps) const override;
};

class Linear : public TimingFunction {
public:
  int operator()(int step, int totalSteps) const override;
};

class EaseInOut : public TimingFunction {
private:
  double factor;

public:
  EaseInOut(double factor) : factor(factor) {};
  int operator()(int step, int totalSteps) const override;
};
