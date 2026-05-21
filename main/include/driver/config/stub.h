/**
 * @brief Configuration settings stub.
 */
#pragma once

#include <cstdint>

#include "driver/config/interface.h"
#include "driver/adc/types.h"
#include "driver/gpio/types.h"
#include "driver/timer/types.h"

#include "driver/adc/stub.h"
#include "driver/gpio/stub.h"
#include "driver/timer/stub.h"
#include "driver/serial/stub.h"
#include "driver/tempsensor/stub.h"

namespace driver::config
{
/**
 * @brief Configuration settings for stub.
 */
class Stub final : public Interface
{
public:

    explicit Stub() noexcept;

    void delay_ms(std::uint16_t ms) noexcept override;

    const adc::Settings& getADC(adc::Id id) const noexcept override;

    const gpio::Settings& getGpio(gpio::Id id) const noexcept override;

    const timer::Settings& getTimer(timer::Id id) const noexcept override; 

    const serial::Settings& getSerial() const noexcept override;

    const tempsensor::Settings& getTempsensor() const noexcept override;

private:
    std::array<adc::StubSettings, static_cast<std::size_t>(adc::Id::COUNT)> adcConfigs_; 
    std::array<gpio::StubSettings, static_cast<std::size_t>(gpio::Id::COUNT)> gpioConfigs_; 
    std::array<timer::StubSettings, static_cast<std::size_t>(timer::Id::COUNT)> timerConfigs_; 
    serial::StubSettings serialConfig_;
    tempsensor::StubSettings tempsensorConfig_; 
};
} // namespace driver::config
