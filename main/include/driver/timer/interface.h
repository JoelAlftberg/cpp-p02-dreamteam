#pragma once

#include <chrono>
#include <cstdint>

namespace driver::timer
{

struct Settings
{
    bool isEnabled = false;
    std::uint32_t timeout_ms = 1000U;
};

class Interface
{
public:
    /**
     * @brief Destructor
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Start the timer.
     */
    virtual void start() noexcept = 0;

    /**
     * @brief Stop the timer.
     */
    virtual void stop() noexcept = 0;

    /**
     * @brief Cheack if the timer is running.
     * 
     * @return True if the timer is running, false otherwise.
     */
    virtual bool isRunning() const noexcept = 0;

    /**
     * @brief Check if the timer has tiemd out.
     * 
     * @return True if the timer has timed out, false otherwise.
     */
    virtual bool hasTimedOut() noexcept = 0;

    /**
     * @brief Toggle the timer.
     */
    virtual void toggle() noexcept = 0;

    /**
     * @brief Increment the timer.
     * 
     * @note This operation is only performed if the timer is running.
     */
    virtual void tick() noexcept = 0;

    /**
     * @brief Set the timeout of the timer
     * 
     * @param[in] timeout_ms Timeout to set in milliseconds
     */
    virtual void setTimeout(std::uint32_t timeout_ms) noexcept = 0;

    /**
     * @brief Get the timeout of the timer
     * 
     * @return The timeout im milliseconds
     */
    virtual std::uint32_t getTimeout() noexcept = 0;
};
} // Namespace timer
