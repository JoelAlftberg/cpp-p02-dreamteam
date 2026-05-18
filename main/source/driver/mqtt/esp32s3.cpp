#include <cstdint>
#include "driver/mqtt/esp32s3.h"

namespace driver::mqtt
{
namespace
{
void eventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    // Hantera MQTT-händelser här.
}
} // namespace
Esp32s3::Esp32s3(const char* url) noexcept
    : myUrl{nullptr == url ? "mqtt://mqtt.eclipseprojects.io" : url}
    , myClient{nullptr}
    {
        const esp_mqtt_client_config_t mqttConfig{
            .broker.address.uri = myUrl,
        };

        myClient = esp_mqtt_client_init(&mqttConfig);
        esp_mqtt_client_register_event(myClient, ESP_EVENT_ANY_ID, eventHandler, myClient);
        esp_mqtt_client_start(myClient);
    }

Esp32s3::~Esp32s3() noexcept
{
    if (nullptr != myClient) {
        esp_mqtt_client_stop(myClient);
        esp_mqtt_client_destroy(myClient);
    }
}

bool Esp32s3::subscribe(const char* topic) noexcept
{
    if(nullptr == topic){ return false; }

    esp_mqtt_client_subscribe(myClient, topic, 1);
    return true;
}
bool Esp32s3::publish(const char* broker, const char* msg) noexcept
{
    return true;
}
bool Esp32s3::publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept
{
    return true;
}
std::uint8_t Esp32s3::receive(char* buf, std::uint8_t bufLen) noexcept
{
    return 0;
}  

}//namespace driver::mqtt