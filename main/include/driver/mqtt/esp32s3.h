/**
 * @brief MQTT driver interface.
 */
#pragma once

#include <cstdint>
#include "driver/mqtt/interface.h"
#include "driver/mqtt.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver interface.
 */
class Esp32s3 final : public Interface
{
public:
    /** @brief Constructor. */

    explicit Esp32s3() noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override = default;

    /**
     * @brief Subscribe to broker.
     *
     * @param[in] broker The broker to subscribe to.
     *
     * @return True on success, false on failure.
     */
    bool subscribe(const char* broker) noexcept override;

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] msg Message to publish.
     *
     * @return True on success, false on failure.
     */
    bool publish(const char* broker, const char* msg) noexcept override;

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] buf Bytes to publish.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return True on success, false on failure.
     */
    bool publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept override;


    /**
     * @brief Receive data from subscribed broker.
     *
     * @param[in] buf Buffer holding received data.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return Number of received bytes, or 0 on failure.
     */
    std::uint8_t receive(char* buf, std::uint8_t bufLen) noexcept override;


    private:
        const char* myUrl;
        esp_mqtt_client_handle_t myClient;

};
} // namespace driver::mqtt
