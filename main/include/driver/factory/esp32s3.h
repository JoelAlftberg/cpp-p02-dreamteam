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

namespace driver::factory
{
class Esp32s3 final : public Interface 
{
public:

    Esp32s3() noexcept = default;

    std::unique_ptr<adc::Interface> adc() noexcept override
    {
        return std::make_unique<adc::Esp32s3>();
    }

    std::unique_ptr<gpio::Interface> gpio() noexcept override
    {
        return std::make_unique<gpio::Esp32s3>();
    }

    std::unique_ptr<serial::Interface> serial() noexcept override
    {
        return std::make_unique<serial::Esp32s3>();
    }

    std::unique_ptr<timer::Interface> timer() noexcept override
    {
        return std::make_unique<timer::Esp32s3>();
    }

    std::unique_ptr<tempsensor::Interface> tempsensor() noexcept override
    {
        return std::make_unique<tempsensor::Esp32s3>();
    }

    std::unique_ptr<config::Interface> config() noexcept override
    {
        return std::make_unique<config::Esp32s3>();
    }
};

}
