#include "Effects.h"
#include "InterpolationCache.h"
#include "TimingFunction.h"
#include "util.h"
#include <cassert>
#include <cwchar>
#include <sys/types.h>

Effects::Effects(Strip *strip) : _strip(strip) {}

template <typename T>
void shiftArrayLeft(std::vector<T> &arr)
{
  for (size_t i = 0; i < arr.size() - 1; i++)
  {
    T current = arr[i];
    int next = i == arr.size() - 1 ? 0 : i + 1;
    arr[i] = arr[next];
    arr[next] = current;
  }
}

template <typename T>
void shiftArrayRight(std::vector<T> &arr)
{
  T prev;
  T current;
  for (size_t i = 0; i < arr.size(); i++)
  {
    current = arr[i];
    arr[i] = i == 0 ? arr[arr.size() - 1] : prev;
    prev = current;
  }
}

template <typename T>
T normalize(T value, T range_min, T range_max)
{
  return value * (range_max - range_min) + range_min;
}

void Effects::pulse(int durationsInMilliseconds, int iterations)
{
  std::vector<Color> lightened = _strip->colors();
  std::vector<Color> darkened = _strip->colors();
  for (auto &color : lightened)
  {
    color.lighten(0.3);
  }
  for (auto &color : darkened)
  {
    color.lighten(-0.3);
  }

  for (int i = 0; i < iterations; i++)
  {
    _strip->fillAll(lightened, durationsInMilliseconds / 2);
    _strip->fillAll(darkened, durationsInMilliseconds / 2);
  }
};

void Effects::christmas()
{
  std::vector<Color> colors(_strip->numberOfLeds);
  size_t count;
  for (size_t i = 0; i < _strip->numberOfLeds; i++)
  {
    colors[i] = count % 2 == 0 ? Color::Red : Color::White;
    if (i % 3 == 0)
    {
      ++count;
    }
  }

  for (size_t i = 0; i < 100; i++)
  {
    _strip->fillAll(colors);
    Utility::wait(2000);
    shiftArrayRight(colors);
  }
}

void Effects::wheel(int iterations, bool reverse = false)
{
  int direction = reverse ? -1 : 1;
  for (int iter = 0; iter < iterations; ++iter)
  {
    for (int shift = 0; shift < _strip->numberOfLeds; ++shift)
    {
      std::vector<Color> colors;
      for (int i = 0; i < _strip->numberOfLeds; i++)
      {
        float hue =
            normalize(1.0 / _strip->numberOfLeds *
                          ((i + shift * direction) % _strip->numberOfLeds),
                      0.0, 360.0);
        if (hue < 0)
        {
          hue += 360.0;
        }
        colors.push_back(Color::fromHSL({hue, 0.7, 0.5}));
      }
      _strip->fillAll(colors, 100);
    }
  }
}

void Effects::shift()
{
  float hue = 0.0;
  Color start = Color::fromHSL({hue, 0.5, 0.5});
  while (1)
  {
    EaseOut e(1.0);
    _strip->fillAll(start, 10000, e);
    Utility::wait(5000);
    start.setHSL(hue = Utility::wrapHue(hue + 60.0), 0.5, 0.5);
  }
}

void Effects::shiftGradient(int iterations)
{
  Color start{255, 0, 0};
  Color end;
  EaseOut timing(1.0);
  auto cache = InterpolationCache::current();
  for (int i = 0; i < iterations; i++)
  {
    end = start.addHue(Utility::rand_between(31.0, 75.0));
    std::vector<Color> colors = cache.get(start, end, _strip->numberOfLeds);
    _strip->fillAll(colors, 3000);
    _strip->fillAll(end, 5000, timing);
    start = end;
  }
}
