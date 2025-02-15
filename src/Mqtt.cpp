#include "Mqtt.h" 

void listen(mqtt::client* client){
    while(true){
        auto msg = client->consume_message();
        auto payload = msg->to_string();
        std::cout << payload << std::endl;
    }
}
