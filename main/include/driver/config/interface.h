/**
 * @brief Configuration interface.
 */
#pragma once

#include <cstdint>

namespace driver::config
{
/**
 * @brief Configuration interface.
 */
class Interface
{
public:
    virtual ~Interface() noexcept = default;
    virtual void delay_ms(std::uint16_t ms) noexcept = 0;

    virtual driver::adc::Settings& get_adc() noexcept = 0;

    virtual driver::gpio::Settings& get_gpio() noexcept = 0;

    virtual driver::timer::Settings& get_timer() noexcept = 0;

    virtual driver::serial::Settings& get_serial() noexcept = 0;

    virtual driver::tempsensor::Settings& get_tempsensor() noexcept = 0;
};
} // namespace driver::config
