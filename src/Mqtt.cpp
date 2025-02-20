#include "Mqtt.h"
#include "Logger.h"

void listen(mqtt::client *client) {
  while (true) {
    auto msg = client->consume_message();
    if (msg) {
      Logger::log("Message arrived", LogLevel::Debug);
      auto payload = msg->to_string();
      std::cout << payload << std::endl;
    }
  }
}
