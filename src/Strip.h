#pragma once
#include "Gradient.h"
#include "LedState.h"
#include "TimingFunction.h"
#include <vector>

class Strip {

public:
  Strip(int leds);
  virtual ~Strip();

  int numberOfLeds;
  LedState *leds;
  std::vector<Color> colors();
  void fillAll(Color color);
  void fillAll(uint32_t color);
  void fillAll(Color color, int durationInMilliseconds);
  void fillAll(Color color, int durationInMilliseconds, TimingFunction &);
  void fillAll(Color *colors);
  void fillAll(Gradient gradient);
  void fillAll(Gradient gradient, int durationInMilliseconds);
  void fillAll(Color *colors, int durationInMilliseconds);
  void fillAll(Color *colors, int durationInMilliseconds, TimingFunction &);
  void fillAll(std::vector<Color> colors, int durationInMilliseconds);
  void fillAll(std::vector<Color> colors, int durationInMilliseconds,
               TimingFunction &);
  void fillAll(std::vector<Color> colors);
  void fillAll(HSL *hsl, int durationInMilliseconds);
  void setRender(bool);
  void setDelay(bool);

private:
  virtual void render() = 0;
  bool shouldRender = true;
  bool shouldWait = true;
};
