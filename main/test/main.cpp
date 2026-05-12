#include <chrono>
#include <cstdint>
#include <thread>

#include "driver/gpio/stub.h"

using namespace driver;

namespace
{
void delay_ms(const std::uint16_t ms) noexcept
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace

int main()
{
    constexpr std::uint8_t ledPin{8U};
    constexpr std::size_t iterationCount{10U};
    constexpr std::uint16_t blinkSpeed_ms{100U};

    gpio::Stub led{ledPin, gpio::Mode::Output};

    for (std::size_t i{}; i < iterationCount; ++i)
    {
        led.toggle();
        delay_ms(blinkSpeed_ms);
    }
}
