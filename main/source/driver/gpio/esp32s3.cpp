//** GPIO-driver for the esp32s3. */

#include "driver/gpio/interface.h"
#include "driver/gpio/esp32s3.h"
#include <cstdint>

namespace driver::gpio
{
    Esp32s3::Esp32s3(const std::uint8_t pin, const Mode mode) noexcept
        : myPin{pin}
        , myMode{mode}
        , myState{false}
    {
        gpio_config_t user_config = {
            .pin_bit_mask = (1ULL << myPin),
            .mode = (myMode == Mode::Input) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        gpio_config(&user_config);
    }
    void Esp32s3::on() noexcept
    {
        gpio_set_level(static_cast<gpio_num_t>(myPin), 1U);
    }
    void Esp32s3::off() noexcept
    {
        gpio_set_level(static_cast<gpio_num_t>(myPin), 0U);
    }
    void Esp32s3::toggle() noexcept
    {
        int level = gpio_get_level(static_cast<gpio_num_t>(myPin));
        level = !level; // Toggle the level
        gpio_set_level(static_cast<gpio_num_t>(myPin), level);
    }
    bool Esp32s3::read() const noexcept
    {
        int level = gpio_get_level(static_cast<gpio_num_t>(myPin));
        return level;
    }


}// namespace driver::gpio