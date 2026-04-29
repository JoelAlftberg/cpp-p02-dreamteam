#include "driver/gpio.h"
#include "driver/gpio/esp32s3.h"
#include <cstdint>

// Här kan du inkludera andra nödvändiga header-filer och implementera funktionerna för ESP32S3 GPIO-drivrutiner.

namespace driver::gpio
{
Esp32s3::init(gpio_num_t pin, gpio_mode_t mode) noexcept
{   
    gpio_config_t user_config = {
        .pin_bit_mask = (1UL << pin),
        .mode = mode,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };   
    
    esp_err_t gpio_config(const gpio_config_t *user_config);
}

//Set GPIO pin to high level
Esp32s3::on(gpio_num_t pin) noexcept
{
    esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level{1U});
}

//Set GPIO pin to low level
Esp32s3::off(gpio_num_t pin) noexcept
{
    esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level{0U});
}

//Toggle GPIO pin state
Esp32s3::toggle(gpio_num_t pin, const std::uint32_t timeout_ms) noexcept
{
    int level = gpio_get_level(gpio_num_t pin);
    level = !level; // Toggle the level
    esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level);
}

//Read GPIO pin state
Esp32s3::read(gpio_num_t pin) noexcept
{
    int level = gpio_get_level(gpio_num_t pin);
    return level;
}
}//namespace driver::gpio
