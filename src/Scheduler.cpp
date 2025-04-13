#include "Scheduler.h"
#include "Color.h"
#include "Effects.h"
#include "InterpolationCache.h"
#include "Logger.h"
#include "Mqtt.h"
#include "Palettes_generated.h"
#include "Strip.h"
#include "TimingFunction.h"
#include "util.h"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <mqtt/connect_options.h>
#include <mutex>
#include <random>
#include <string>

using namespace std::chrono_literals;

Scheduler::Scheduler(Strip *strip)
    : strip(strip), mqtt_client("tcp://192.168.0.126:1883", "LIGHTS") {
  setup_mqtt();
}

void Scheduler::setup_mqtt() {
#ifndef USE_MQTT
  Logger::log("Skipping MQTT setup", Info);
  return;
#else
  auto &client = this->mqtt_client;
  auto opts = mqtt::connect_options_builder()
                  .keep_alive_interval(30s)
                  .clean_session(false)
                  .automatic_reconnect()
                  .finalize();
  client.start_consuming();
  auto res = client.connect(opts);
  if (!res.is_session_present()) {
    Logger::log("Subscribing to MQTT topic 'LIGHTS'", Debug);
    client.subscribe({"LIGHTS"}, 1);
  }
  std::thread thread(listen, &(this->mqtt_client));
  thread.detach();
#endif
}

std::queue<std::string> Scheduler::queue = std::queue<std::string>();
std::mutex Scheduler::queue_mutex = std::mutex();

void Scheduler::enqueue(std::string s) {
  std::lock_guard<std::mutex> lock(Scheduler::queue_mutex);
  Scheduler::queue.push(s);
}

bool Scheduler::should_run() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto tm = std::localtime(&time);
  return tm->tm_hour > 8;
}

void Scheduler::pause() {
  this->strip->fillAll(Color{23, 23, 23});
  Logger::log("Pausing for 10 minutes", Info);
  Utility::wait(1000 * 60 * 10);
}

void Scheduler::run() {
  if (!this->strip) {
    std::cerr << "No strip found!" << std::endl;
    std::exit(-1);
  }
  while (1) {
    if (!should_run()) {
      pause();
      continue;
    }
    auto x = std::rand() % 7;
    Logger::log("Starting routine " + std::to_string(x+1), Info);
    switch (x) {
    case 0:
      routine1();
      break;
    case 1:
      routine2();
      break;
    case 2:
      routine3();
      break;
    case 3:
      routine4();
      break;
    case 4:
      routine5();
      break;
    case 5:
      routine6();
      break;
    case 6:
      routine7();
      break;
    case 7:
      routine8();
      break;
    case 8:
      routine9();
      break;
    case 9:
      routine10();
      break;
    }
    Logger::log("Cache hit ratio: " + std::to_string(InterpolationCache::current().cacheHitRatio()), Debug);
    Logger::log("Cache size: " + std::to_string(InterpolationCache::current().size()),Debug);
  }
}

void Scheduler::routine1() {
  auto color1 = Color::random();
  auto color2 = color1.addHue(60);
  auto interpolation = color1.interpolate(color2, strip->numberOfLeds);
  auto reversed = interpolation;
  std::reverse(reversed.begin(), reversed.end());
  EaseIn timing(1);
  for (int i = 0; i < 25; i++) {
    strip->fillAll(interpolation, 5000, timing);
    strip->fillAll(reversed, 5000, timing);
  }
};

void Scheduler::routine2() {
  Effects eff(strip);
  eff.wheel(5, false);
  eff.wheel(10, true);
}

void Scheduler::routine3() {
  Effects eff(strip);
  eff.shiftGradient(13);
}

void Scheduler::routine4() {
  std::random_device d;
  std::mt19937 gen(d());

  std::vector<Color> colors = {
      Color::Olive,  Color::Gold, Color::Orange,  Color::Lime,   Color::Red,
      Color::Purple, Color::Blue, Color::Magenta, Color::Yellow, Color::Teal,
  };

  for (int i = 0; i < 5; ++i) {
    std::vector<Color> sampled;
    std::sample(colors.begin(), colors.end(), std::back_inserter(sampled), 3,
                gen);
    Gradient gradient(sampled);
    strip->fillAll(gradient, i == 0 ? 4000 : 20000);
  }
}

void Scheduler::routine5() {
  auto colors = std::vector<HSL>{HSL{356, 0.82, 0.55}, HSL{23, 0.6, 0.82},
                                 HSL{49, 1.0, 0.91}};
  Gradient gradient(colors);
  strip->fillAll(gradient, 1000);
}

void Scheduler::routine6() {
  size_t count;
  int speed = Utility::rand_between(30, 120);
  auto palettes = shuffled_palettes();
  for (auto &palette : palettes) {
    std::vector<Color> colors =
        Utility::divide_blocks(palette, strip->numberOfLeds);
    for (size_t i = 0; i < 200; i++) {
      strip->fillAll(colors, speed);
      Utility::shiftArrayLeft(colors);
    }
  }
}
void Scheduler::routine7() {
  size_t count;
  Effects eff(strip);
  int speed = Utility::rand_between(500, 5000);
  auto palettes = shuffled_palettes();
  for (auto &palette : palettes) {
    std::vector<Color> colors =
        Utility::divide_blocks(palette, strip->numberOfLeds);
    strip->fillAll(colors, speed);

    eff.pulse(2900, 12);
  }
}
void Scheduler::routine8() {
  auto palettes = shuffled_palettes();
  int block_sizes[] = {15, 10, 7, 5};
  std::vector<palette> p;
  for (auto &plt : palettes) {
    std::vector<palette> interm;
    for (int i : block_sizes) {
      interm.push_back(Utility::divide_blocks(plt, strip->numberOfLeds, i));
    }
    for (auto it = interm.rbegin(); it != interm.rend(); ++it) {
      p.push_back(*it);
    }
    for (auto it = interm.rbegin(); it != interm.rend(); ++it) {
      p.push_back(*it);
    }
  }
  Logger::log("Palettes size: " + std::to_string(p.size()), Debug);
  for (auto i = 0; i < p.size(); ++i) {
    strip->fillAll(p[i], 700);
    Utility::wait(200);
    if ((i + 1) % 8 == 0) {
      Utility::wait(1200);
    }
  }
}

void Scheduler::routine9() {
  Logger::log("Starting routine9", Debug);
  for (int i = 1; i < 6; ++i) {
    EaseInOut t(2);
    strip->fillAll(Color::Blue, 3000, t);
    strip->fillAll(Color::Red, 3000, t);
  }
}

void Scheduler::routine10() {
  Logger::log("Starting routine10", Debug);
  Gradient grad({Color::Orange, Color::Purple});
  strip->fillAll(grad, 3000);
  Utility::wait(120000);
  Gradient grad2({Color{0x9d, 0, 0xff}, Color{0xff, 0, 0}, Color{0xed, 0xdb, 0x53}});
  strip->fillAll(grad2, 8000);
  Utility::wait(120000);
}
