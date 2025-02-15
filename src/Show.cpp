#include "Show.h"
#include "Color.h"
#include "Effects.h"
#include "Strip.h"
#include "Mqtt.h"
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <mqtt/connect_options.h>
#include <mutex>
#include <random>

using namespace std::chrono_literals;

Show::Show(Strip *strip)
    : strip(strip), mqtt_client("tcp://192.168.0.126:1883", "LIGHTS") {
  setup_mqtt();
}


bool msg_handler(const mqtt::message &msg){
    return true;
}



void Show::setup_mqtt(){
    std::cout << "hello?" << std::endl;
    auto& client = this->mqtt_client;
    auto opts = mqtt::connect_options_builder::v3()
        .keep_alive_interval(30s)
        .clean_session(false)
        .automatic_reconnect()
        .finalize();
    client.start_consuming();
    auto res = client.connect(opts);
    if(!res.is_session_present()){
        std::cout << "Subscribing..." << std::endl;
        client.subscribe({"LIGHTS"}, 1);
    }
    std::cout << "Spawning da thread" << std::endl;
    std::thread thread(listen, &(this->mqtt_client));
    thread.detach();
}

std::queue<std::string> Show::queue = std::queue<std::string>();
std::mutex Show::queue_mutex = std::mutex();

void Show::enqueue(std::string s) {
  std::lock_guard<std::mutex> lock(Show::queue_mutex);
  Show::queue.push(s);
}

void Show::run() {
  if (this->strip == nullptr) {
    std::cerr << "NULL!" << std::endl;
    std::exit(-1);
  }
  while (1) {
    auto x = std::rand() % 7;
    switch (x) {
    case 0:
      routine1();
    case 1:
      routine2();
    case 2:
      routine3();
    case 3:
      routine4();
    case 4:
      routine5();
    case 5:
      routine6();
    case 6:
      routine7();
    }
  }
}

void Show::routine1() {
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

void Show::routine2() {
  Effects eff(strip);
  eff.wheel(5, false);
  eff.wheel(10, true);
}

void Show::routine3() {
  Effects eff(strip);
  eff.shiftGradient(13);
}

void Show::routine4() {
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

void Show::routine5() {
  auto colors = std::vector<HSL>{HSL{356, 0.82, 0.55}, HSL{23, 0.6, 0.82},
                                 HSL{49, 1.0, 0.91}};
  Gradient gradient(colors);
  strip->fillAll(gradient, 1000);
}

void Show::routine6() {
  Effects eff(strip);
  eff.palettes();
}
void Show::routine7() {
  Effects eff(strip);
  eff.palettes_static();
}
