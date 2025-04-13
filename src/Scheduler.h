#pragma once

#include "Strip.h"
#include <mqtt/client.h>
#include <mutex>
#include <queue>

class Scheduler {

private:
  Strip *strip;
  static std::mutex queue_mutex;
  static std::queue<std::string> queue;
  mqtt::client mqtt_client;
  void setup_mqtt();
  bool should_run();
  void pause();

public:
  Scheduler(Strip *strip);
  void routine1();
  void routine2();
  void routine3();
  void routine4();
  void routine5();
  void routine6();
  void routine7();
  void routine8();
  void routine9();
  void routine10();
  static void enqueue(std::string);
  void run();
};
