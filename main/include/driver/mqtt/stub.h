 /**
 * @brief MQTT driver interface.
 */
#pragma once

#include <cstdint>
#include <cstdio>
#include "driver/mqtt/interface.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver stub.
 */
class Stub final : public Interface
{
public:
    explicit Stub() noexcept :
    myInput{0U}{
        std::printf("MQTT Stub initialized\n");
    }
    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Subscribe to broker.
     *
     * @param[in] broker The broker to subscribe to.
     *
     * @return True on success, false on failure.
     */
    bool subscribe(const char* broker) noexcept override{
        if(nullptr == broker){ return false;}
        return true;
    }

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] msg Message to publish.
     *
     * @return True on success, false on failure.
     */
    bool publish(const char* broker, const char* msg) noexcept override{
        // Print message if valid.
        if ((nullptr == msg) || (nullptr == broker)) { return false; }
        std::printf("%s", msg);
        return true;
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
    bool publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept override{
     
         // Check buffer, terminate if invalid.
        if ((nullptr == buf) || (0U == bufLen) || (nullptr == broker)) { return false; }

        // Write each byte one by one.
        for (std::uint16_t i{}; i < bufLen; ++i) 
        { 
            std::printf("%u", buf[i]); 
        }
        std::printf("\n");
        return true;
    }
    /**
     * @brief Receive data from subscribed broker.
     *
     * @param[in] buf Buffer holding received data.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return Number of received bytes, or 0 on failure.
     */
    std::uint8_t receive(char* buf, std::uint8_t bufLen) noexcept override{
         // Check buffer, terminate if invalid.
        if ((nullptr == buf) || (0U == bufLen)) { return 0U; }

        buf[0] = static_cast<char>(myInput);
        return 1U;

    }
    void simulateInput(std::uint8_t input) noexcept override{ 
        myInput = input;
    }
    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Simulated input. */
    std::uint8_t myInput;
    
};
} // namespace driver::mqtt