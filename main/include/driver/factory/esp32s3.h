#pragma once

#include <cstdint>
#include <memory>

#include "driver/serial/interface.h"
#include "driver/factory/interface.h"
#include "driver/adc/esp32s3.h"
#include "driver/config/esp32s3.h"
#include "driver/gpio/esp32s3.h"
#include "driver/tempsensor/esp32s3.h"
#include "driver/timer/esp32s3.h"
#include "driver/mqtt/esp32s3.h"

namespace driver::factory
{
class Esp32s3 final : public Interface 
{
public:

    Esp32s3() noexcept = default;

    std::unique_ptr<adc::Interface> adc(std::uint8_t pin) const noexcept override
    {
        return std::make_unique<adc::Esp32s3>(pin);
    }

    std::unique_ptr<gpio::Interface> gpio(std::uint8_t pin, gpio::Mode mode) const noexcept override
    {
        return std::make_unique<gpio::Esp32s3>(pin, mode);
    }

    std::unique_ptr<serial::Interface> serial(serial::Config config) noexcept override
    {
        return std::make_unique<serial::Esp32s3>(config);
    }

    std::unique_ptr<timer::Interface> timer(std::uint16_t timeout_ms) const noexcept override
    {
        return std::make_unique<timer::Esp32s3>(timeout_ms);
    }

    std::unique_ptr<tempsensor::Interface> tempsensor() noexcept override
    {
        return std::make_unique<tempsensor::Esp32s3>();
    }


};

}
