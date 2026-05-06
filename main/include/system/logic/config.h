#include <cstdint>

namespace system::logic
{


struct GpioConfig
{
    std::uint8_t pin;
    driver::gpio::Mode mode;
};

struct Config
{
    driver::serial::Config config;
    std::vector<GpioConfig> gpioPins;
    std::vector<std::uint8_t>  adcChannels;
    std::vector<std::uint16_t> timers;
};

}
