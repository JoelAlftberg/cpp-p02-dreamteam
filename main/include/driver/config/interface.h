/**
 * @brief Configuration interface.
 */
#pragma once

#include <cstdint>

#include "driver/adc/types.h"
#include "driver/gpio/types.h"
#include "driver/timer/types.h"

namespace driver
{
    namespace adc { class Interface; struct Settings; }
    namespace gpio { class Interface; struct Settings; }
    namespace serial { class Interface; struct Settings; }
    namespace timer { class Interface; struct Settings; }
    namespace tempsensor { class Interface; struct Settings;}
    namespace config { class Interface; struct Settings;}
} // namespace driver

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

    virtual const driver::adc::Settings& getADC(adc::Id id) const noexcept = 0;

    virtual const driver::gpio::Settings& getGpio(gpio::Id id) const noexcept = 0;

    virtual const driver::timer::Settings& getTimer(timer::Id id) const noexcept = 0;

    virtual const driver::serial::Settings& getSerial() const noexcept = 0;

    virtual const driver::tempsensor::Settings& getTempsensor() const noexcept = 0;
};
} // namespace driver::config
