#include "driver/mqtt/esp32s3.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"

namespace driver::mqtt{

static const char* TAG = "MQTT";

static void mqttEventHandler(
    void* handler_args,
    esp_event_base_t base,
    int32_t event_id,
    void* event_data)
{
    esp_mqtt_event_handle_t event =
        static_cast<esp_mqtt_event_handle_t>(event_data);

    if (event->event_id == MQTT_EVENT_CONNECTED)
    {
        ESP_LOGI(TAG, "Connected to broker");
    }
}
<<<<<<< HEAD

Esp32s3::Esp32s3() noexcept
        :myUrl{},
        myClient{}
{

    // Required init
    nvs_flash_init();

    // MQTT configuration
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_BROKER,
    };

    // Create client
    esp_mqtt_client_handle_t client =
        esp_mqtt_client_init(&mqtt_cfg);

    // Register event handler
    esp_mqtt_client_register_event(
        client,
        ESP_EVENT_ANY_ID,
        mqtt_event_handler,
        NULL);
    // Start MQTT
    esp_mqtt_client_start(client);
}
/**
    * @brief Destructor.
    */
Esp32s3::~Esp32s3() noexcept = default;
=======
Esp32s3::Esp32s3(const char* url) noexcept
    : myUrl{nullptr == url ? "mqtt://mqtt.eclipseprojects.io" : url}
    , myClient{nullptr}
    {
        const esp_mqtt_client_config_t mqttConfig{
            .broker.address.uri = myUrl,};
        myClient = esp_mqtt_client_init(&mqttConfig);
        esp_mqtt_client_register_event(myClient, ESP_EVENT_ANY_ID, eventHandler, myClient);
        esp_mqtt_client_start(myClient);
    }
/**
    * @brief Destructor.
    */
Esp32s3::~Esp32s3() noexcept
{
    if (nullptr != myClient) {
        esp_mqtt_client_stop(myClient);
        esp_mqtt_client_destroy(myClient);
    }
}
>>>>>>> f06c0de (did som changes)
/**
    * @brief Subscribe to broker.
    *
    * @param[in] broker The broker to subscribe to.
    *
    * @return True on success, false on failure.
    */
bool Esp32s3::subscribe(const char* broker) noexcept{
    if(nullptr == broker){ return false;}
<<<<<<< HEAD
    int mySub = esp_mqtt_client_subscribe(myClient, broker, 1);
    return (mySub >= 0);
=======
    esp_mqtt_client_subscribe(myClient, broker, 1);
    return true;
>>>>>>> f06c0de (did som changes)
}
/**
    * @brief Public message to broker.
    *
    * @param[in] broker Broker for which to publish.
    * @param[in] msg Message to publish.
    *
    * @return True on success, false on failure.
    */
bool Esp32s3::publish(const char* broker, const char* msg) noexcept{
    if ((nullptr == msg) || (nullptr == broker)) { return false; }
<<<<<<< HEAD
    int myPub =  esp_mqtt_client_publish(
            myClient,
            broker,
            msg,
            0,
            0,
            0);
    return (myPub >= 0);
=======
    esp_mqtt_client_publish(myClient, broker, msg, 0, 0, 0);
    return true;
>>>>>>> f06c0de (did som changes)
}
/**
    * @brief Public message to broker.
    *
    * @param[in] broker Broker for which to publish.
    * @param[in] buf Bytes to publish.
    * @param[in] bufLen Buffer length in bytes.
    *
    * @return True on success, false on failure.
    */
bool Esp32s3::publisher(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept{
    if ((nullptr == buf) || (0U == bufLen) || (nullptr == broker)) { return false; }
<<<<<<< HEAD
    int myPub =  esp_mqtt_client_publish(
            myClient,
            broker,
            buf,
            bufLen,
            0,
            0);
    return (myPub >= 0);
=======
    esp_mqtt_client_publish(myClient, broker, buf, bufLen, 0, 0);
    return true;
>>>>>>> f06c0de (did som changes)
}
/**
    * @brief Receive data from subscribed broker.
    *
    * @param[in] buf Buffer holding received data.
    * @param[in] bufLen Buffer length in bytes.
    *
    * @return Number of received bytes, or 0 on failure.
    */
std::uint8_t Esp32s3::receive(char* buf, std::uint8_t bufLen) noexcept{
    if ((nullptr == buf) || (0U == bufLen)) { return 0U; }
<<<<<<< HEAD

}

  
}
   
   
=======
    if(subscribe()){
        return bufLen;
    }
    esp_mqtt_client_unsubscribe(myClient, buf);
    return 0U;
}
}
>>>>>>> f06c0de (did som changes)
