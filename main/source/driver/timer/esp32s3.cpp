#include "esp_timer.h"
#include "driver/timer/esp32s3.h"

namespace driver::timer
{
Esp32s3::Esp32s3(const std::uint16_t timeout_ms) noexcept
    : myTimeout_us{static_cast<std::int64_t>(timeout_ms) * 1000LL}
    , myCounter_us{0}
    , myLastTime_us{0}
    , myRunning{false}

{}

void Esp32s3::start() noexcept
{
    if (!myRunning)
    {
        myLastTime_us = esp_timer_get_time();
        myRunning = true;
    }
}

void Esp32s3::stop() noexcept 
{
    if (myRunning)
    {
        updateCounter();
        myRunning = false;
    }
}

bool Esp32s3::isRunning() const noexcept { return myRunning; }

bool Esp32s3::hasTimedOut() noexcept 
{
    if (!myRunning) { return false; }

    updateCounter();

    const bool timeout{myCounter_us >= myTimeout_us};

    if (timeout) { myCounter_us = 0; }

    return timeout;
}
void Esp32s3::toggle() noexcept { myRunning ? stop() : start(); }

void Esp32s3::tick() noexcept 
{
    if (myRunning) { updateCounter(); }
}

void Esp32s3::setTimeout(std::uint32_t timeout_ms) noexcept
{
    myTimeout_us = timeout_ms * 1000U;
}

std::uint32_t Esp32s3::getTimeout() noexcept
{
    return myTimeout_us / 1000;
}    

void Esp32s3::updateCounter() noexcept
{
    const int64_t currentTime_us = esp_timer_get_time();
    myCounter_us += (currentTime_us - myLastTime_us);
    myLastTime_us = currentTime_us;
}
} // Namespace timer