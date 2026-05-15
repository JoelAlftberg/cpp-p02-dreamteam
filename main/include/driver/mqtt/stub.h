 /**
 * @brief MQTT driver interface.
 */
#pragma once

#include <cstdint>

namespace driver::mqtt
{
/**
 * @brief MQTT driver stub.
 */
class Stub
{
public:
    Stub() noexcept{

    }

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept = default;

    /**
     * @brief Subscribe to broker.
     *
     * @param[in] broker The broker to subscribe to.
     *
     * @return True on success, false on failure.
     */
    bool subscribe(const char* broker) noexcept {

    }

    /**
     * @brief Public message to broker.
     *
     * @param[in] broker Broker for which to publish.
     * @param[in] msg Message to publish.
     *
     * @return True on success, false on failure.
     */
    bool publish(const char* broker, const char* msg) noexcept {
        // Print message if valid.
        if ((nullptr != msg) || (nullptr == broker)) { 
            std::printf("%s", msg); 
            return false;
        }else{
            return true;
        }

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
    bool publish(const char* broker, const std::uint8_t* buf, std::uint8_t bufLen) noexcept {
     
         // Check buffer, terminate if invalid.
        if ((nullptr == buf) || (0U == bufLen) || (nullptr == broker)) { return false; }

        // Write each byte one by one.
        for (std::uint16_t i{}; i < bufLen; ++i) 
        { 
            std::printf("%u", buf[i]); 
        }

    }

    /**
     * @brief Receive data from subscribed broker.
     *
     * @param[in] buf Buffer holding received data.
     * @param[in] bufLen Buffer length in bytes.
     *
     * @return Number of received bytes, or 0 on failure.
     */
    std::uint8_t receive(char* buf, std::uint8_t bufLen) noexcept {
         // Check buffer, terminate if invalid.
        if ((nullptr == buf) || (0U == bufLen)) { return 0U; }

        // Write each byte one by one.
        for (std::uint16_t i{}; i < bufLen; ++i) 
        { 
            std::printf("%u", buf[i]); 
            return myInput;
        }

    }
    void simulateInput(std::uint16_t input) noexcept { 
        myInput = input;
    }
    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    bool myState;
    /** Simulated input. */
    std::uint16_t myInput;
    
};
} // namespace driver::mqtt