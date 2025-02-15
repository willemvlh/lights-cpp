#pragma once

#include "Strip.h"
#include <functional>
#include <mqtt/client.h>
#include <mutex>
#include <queue>

class Show {

private:
  Strip *strip;
  static std::mutex queue_mutex;
  static std::queue<std::string> queue;
  mqtt::client mqtt_client;
  void setup_mqtt();

public:
  Show(Strip *strip);
  void routine1();
  void routine2();
  void routine3();
  void routine4();
  void routine5();
  void routine6();
  void routine7();
  static void enqueue(std::string);
  void run();
};
