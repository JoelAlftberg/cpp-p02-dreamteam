#pragma once

#include <cstdint>
#include <memory>

#include "driver/factory/interface.h"

namespace driver::factory
{

class Stub final : public Interface 
{
public:
    
    explicit Stub() noexcept
        : config_{std::move(config)}
    {}

    std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept override
    {
        return std::make_unique<adc::Stub>();
    }

    std::unique_ptr<gpio::Interface> gpio(std::uint8_t pin, gpio::Mode mode) noexcept override
    {
        return std::make_unique<gpio::Stub>();
    }

    std::unique_ptr<serial::Interface> serial(serial::Config config) noexcept override
    {
        return std::make_unique<serial::Stub>();
    }

    std::unique_ptr<timer::Interface> timer(std::uint16_t timeout_ms) noexcept override
    {
        return std::make_unique<timer::Stub>(timeout_ms);
    }

    std::unique_ptr<tempsensor::Interface> tempsensor() noexcept override
    {
        return std::make_unique<tempsensor::Stub>();
    }

    std::unique_ptr<config::Interface> config() noexcept override
    {
        return std::make_unique<config::Stub>();
    }

};
    
}
