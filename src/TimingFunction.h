#pragma once

#include <cmath>
#include <cstdio>
class TimingFunction {
public:
  virtual float operator()(float t) const = 0;
};

class EaseIn : public TimingFunction {
private:
  double factor;

public:
  EaseIn(double factor) : TimingFunction(), factor(factor) {};
  float operator()(float t) const override;
};

class EaseOut : public TimingFunction {
private:
  double factor;

public:
  EaseOut(double factor) : factor(factor) {};
  float operator()(float t) const override;
};

class Linear : public TimingFunction {
public:
  float operator()(float t) const override;
};

class EaseInOut : public TimingFunction {
private:
  double factor;

public:
  EaseInOut(double factor) : factor(factor) {};
  float operator()(float t) const override;
};
