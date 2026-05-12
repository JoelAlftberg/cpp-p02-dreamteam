#pragma once

#include <cstdint>
#include <memory>

#include "driver/factory/interface.h"

#include "driver/adc/stub.h"
#include "driver/gpio/stub.h"
#include "driver/serial/stub.h"
#include "driver/timer/stub.h"
#include "driver/tempsensor/stub.h"

namespace driver::factory
{

class Stub final : public Interface 
{
public:
    
    explicit Stub() noexcept
    {}

    std::unique_ptr<adc::Interface> adc(const adc::Settings& settings) const noexcept override
    {
        return std::make_unique<adc::Stub>();
    }

    std::unique_ptr<gpio::Interface> gpio(const gpio::Settings& settings) const noexcept override
    {
        const auto& gpioSettings = static_cast<const gpio::StubSettings&>(settings);
        return std::make_unique<gpio::Stub>(gpioSettings.pin, gpioSettings.mode);
    }

    std::unique_ptr<serial::Interface> serial(const serial::Settings& settings) const noexcept override
    {
        return std::make_unique<serial::Stub>();
    }

    std::unique_ptr<timer::Interface> timer(const timer::Settings& settings) const noexcept override
    {
        const auto& timerSettings = static_cast<const timer::StubSettings&>(settings);
        return std::make_unique<timer::Stub>(timerSettings.timeout_ms);
    }

    std::unique_ptr<tempsensor::Interface> tempsensor(
            const tempsensor::Settings& settings
            ) const noexcept override
    {
        return std::make_unique<tempsensor::Stub>();
    }

};
    
}
