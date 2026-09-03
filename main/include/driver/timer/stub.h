#pragma once

#include <cstdint>

#include "driver/timer/interface.h"

namespace driver::timer
{
struct StubSettings final : public Settings{};

class Stub final : public Interface
{
public:
    explicit Stub(const std::uint16_t timeout_ms) noexcept
        : myTimeout_us{static_cast<std::int64_t>(timeout_ms) * 1000LL}
        , myCounter_us{0U}
        , myLastTime_us{0}
        , myRunning{false}
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default; 

    /**
     * @brief Start the timer.
     */
    void start() noexcept override { myRunning = true; }

    /**
     * @brief Stop the timer.
     */
    void stop() noexcept override { myRunning = false; }

    /**
     * @brief Cheack if the timer is running.
     * 
     * @return True if the timer is running, false otherwise.
     */
    bool isRunning() const noexcept override { return myRunning; }

    /**
     * @brief Check if the timer has tiemd out.
     * 
     * @return True if the timer has timed out, false otherwise.
     */
    bool hasTimedOut() noexcept override
    {
        if (!myRunning) { return false; }
        const bool timeout{myTimeout_us <= myCounter_us}; 
        if (timeout) { myCounter_us = 0U; }
        return timeout;
    }

    /**
     * @brief Toggle the timer.
     */
    void toggle() noexcept override { myRunning = !myRunning; }

    /**
     * @brief Increment the timer.
     * 
     * @note This operation is only performed if the timer is running.
     */
    void tick() noexcept override
    {
        // Consider using a constexpr instead of the magic number 10000U:
        // constexpr std::int64_t increment{10000};

        /** The number 10000 is tied to the task delay in main of 10 ms **/
        if (myRunning) { myCounter_us += 10000U; }
    }

    void setTimeout(std::uint32_t timeout_ms) noexcept override
    {
        myTimeout_us = timeout_ms * 1000U;
    }

    std::uint32_t getTimeout() noexcept override
    {
        return myTimeout_us / 1000;
    }

    Stub()                      = delete;
    Stub(const Stub&)           = delete;
    Stub(Stub&&)                = delete;
    Stub operator=(const Stub&) = delete;
    Stub& operator=(Stub&&)     = delete;

private:

    // Remove this declaration - the method does not exist.
    void updateCounter() noexcept;

    /** Timeout in microseconds. */
    std::int64_t myTimeout_us;

    /** Internal microseconds counter. */
    std::int64_t myCounter_us;

    /** Last (previous) timestamp. */
    std::int64_t myLastTime_us;
    
    /** True if the timer is running, false otherwise. */
    bool myRunning;
};
} // namespace timer
