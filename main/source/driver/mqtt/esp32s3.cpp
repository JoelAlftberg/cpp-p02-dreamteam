#include <cstdint>
#include <string>

#include "driver/mqtt/esp32s3.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"

namespace driver::mqtt{
namespace
{
constexpr const char* Tag{"MQTT"};
constexpr const char* DefaultUrl{"mqtt://mqtt.eclipseprojects.io"};
} // namespace

// -------------------------------------------------------------------
Esp32s3::Esp32s3(const char* url) noexcept
    : myBuf{}
    , myUrl{nullptr == url ? DefaultUrl : url}
    , myBufLen{}
    , myClient{nullptr}
    {
        // Create MQTT configuration and client, register event handler and start client.
        const esp_mqtt_client_config_t mqttConfig{
            .broker.address.uri = myUrl
        };
        myClient = esp_mqtt_client_init(&mqttConfig);
        esp_mqtt_client_register_event(myClient, ESP_EVENT_ANY_ID, mqttEventHandler, myClient);
        esp_mqtt_client_start(myClient);
    }

// -------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{
    // Stop and destroy MQTT client if it exists.
    if (nullptr != myClient) {
        esp_mqtt_client_stop(myClient);
        esp_mqtt_client_destroy(myClient);
    }
}

// -------------------------------------------------------------------
bool Esp32s3::subscribe(const char* broker) noexcept
{
    constexpr int qos{1};
    // Check broker, return false if invalid.
    if(nullptr == broker) { return false; }

    // Subscribe to the broker with QoS 1.
    esp_mqtt_client_subscribe(myClient, broker, qos);
    return true;
}

// -------------------------------------------------------------------
bool Esp32s3::publish(const char* broker, const char* msg) noexcept
{
    // Check broker and message, return false if invalid.
    if ((nullptr == msg) || (nullptr == broker)) { return false; }

    // Publish the message to the broker with QoS 0 and no retain.
    esp_mqtt_client_publish(myClient, broker, msg, 0, 0, 0);
    return true;
}

// -------------------------------------------------------------------
bool Esp32s3::publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept
{
    // Check broker and buffer, return false if invalid.
    if ((nullptr == buf) || (0U == bufLen) || (nullptr == broker)) { return false; }

    // Publish the buffer to the broker with QoS 0 and no retain.
    esp_mqtt_client_publish(myClient, broker, buf, bufLen, 0, 0);
    return true;
}

// -------------------------------------------------------------------
std::uint8_t Esp32s3::receive(char* buf, std::uint8_t bufLen) noexcept
{
    // Check buffer, return 0 if invalid.
    if ((nullptr == buf) || (0U == bufLen)) { return 0U; }

    // Copy data from internal RX buffer to provided buffer, ensure null termination.
    const auto bytesToCopy = (myRxBufLen < bufLen) ? myRxBufLen : (bufLen - 1U);

    for (std::uint8_t i{}; i < bytesToCopy; ++i) 
    { 
        buf[i] = myRxBuf[i]; 
    }
    // Ensure null termination
    buf[bytesToCopy] = '\0';

    // Return number of copied bytes.
    return bytesToCopy;
}

// -------------------------------------------------------------------
void Esp32s3::mqttEventHandler(void* handler_args, esp_event_base_t base,
         int32_t event_id, void* event_data)
{
    auto instance = static_cast<Esp32s3*>(handler_args);
    auto event    = static_cast<esp_mqtt_event_handle_t>(event_data);

    // Check instance and event, return if invalid.
    if ((nullptr == instance) || (nullptr == event)) { return; }

     switch (event->event_id)
    {
        case MQTT_EVENT_CONNECTED:
        {
            ESP_LOGI(Tag, "Connected to broker");
            break;
        }

        case MQTT_EVENT_DATA:
        {
            // Skriver ut data temporärt för loggning.
            {
                ESP_LOGI(Tag, "Incoming data");
                 // Topic
                const std::string topic(event->topic, event->topic_len);

                // Payload
                const std::string payload(event->data, event->data_len);

                ESP_LOGI(Tag, "Topic: %s", topic.c_str());
                ESP_LOGI(Tag, "Payload: %s", payload.c_str());
            }
            instance->storeReceivedData(event->data, event->data_len);
            break;
        }

        default:
            break;
    }
}

// -------------------------------------------------------------------
void Esp32s3::storeReceivedData(const char* data, std::uint8_t dataLen) noexcept
{
    // Check data, return if invalid.
    if ((nullptr == data) || (0U == dataLen)) { return; }

    // Set new RX buf len, ensure that it does not exceed the maximum buffer length.
    myRxBufLen = (dataLen < MaxBufLen) ? dataLen : MaxBufLen;

    // Copy received data to RX buffer, ensure null termination.
    for (std::uint8_t i{}; i < myRxBufLen; ++i) 
    { 
        myRxBuf[i] = data[i]; 
    }
}
} // namespace driver::mqtt