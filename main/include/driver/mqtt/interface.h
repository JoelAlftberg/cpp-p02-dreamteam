/**
 * @brief MQTT driver interface.
 */
#pragma once

#include <cstdint>

namespace driver::mqtt
{

struct Settings
{

};

/**
 * @brief MQTT driver interface.
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    virtual void startClient() noexcept = 0;

    /**
     * @brief Subscribe to broker.
     *
     * @param[in] broker The broker to subscribe to.
     *
     * @return True on success, false on failure.
     */
    virtual bool subscribe(const char* broker) noexcept = 0;

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] msg Message to publish.
     *
     * @return True on success, false on failure.
     */
    virtual bool publish(const char* broker, const char* msg) noexcept = 0;

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] buf Bytes to publish.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return True on success, false on failure.
     */
    virtual bool publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept = 0;


    /**
     * @brief Receive data from subscribed broker.
     *
     * @param[in] buf Buffer holding received data.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return Number of received bytes, or 0 on failure.
     */
    virtual std::uint8_t receive(char* buf, std::uint8_t bufLen) noexcept = 0;
};
} // namespace driver::mqtt
