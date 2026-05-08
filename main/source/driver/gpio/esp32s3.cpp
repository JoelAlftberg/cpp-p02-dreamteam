//** GPIO-driver for the esp32s3. */

#include "driver/gpio/interface.h"
#include "driver/gpio/esp32s3.h"
#include <cstdint>

namespace
{
constexpr gpio_num_t gpioNum(const std::uint8_t pin) noexcept
{
    return static_cast<gpio_num_t>(pin);
}
}

namespace driver::gpio
{
    Esp32s3::Esp32s3(const std::uint8_t pin, const Mode mode) noexcept
        : myPin{pin}
        , myMode{mode}
        , myState{false}
    {
        gpio_config_t conf{};
        conf.pin_bit_mask = (1ULL << myPin);
        conf.mode = (myMode == Mode::Input) ? GPIO_MODE_INPUT : GPIO_MODE_INPUT_OUTPUT;
        conf.pull_up_en = GPIO_PULLUP_DISABLE;
        conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        conf.intr_type = GPIO_INTR_DISABLE;
        gpio_config(&conf);
    }

    Esp32s3::~Esp32s3() noexcept
    {
        gpio_reset_pin(gpioNum(myPin));
    }
    void Esp32s3::on() noexcept
    {
        constexpr std::uint32_t high{1U};
        gpio_set_level(gpioNum(myPin), high);
    }
    void Esp32s3::off() noexcept
    {
        constexpr std::uint32_t low{0U};
        gpio_set_level(gpioNum(myPin), low);
    }
    void Esp32s3::toggle() noexcept
    {
        gpio_set_level(gpioNum(myPin), !read());
    }
    bool Esp32s3::read() const noexcept
    {
        return static_cast<bool>(gpio_get_level(gpioNum(myPin)));
    }
}// namespace driver::gpio