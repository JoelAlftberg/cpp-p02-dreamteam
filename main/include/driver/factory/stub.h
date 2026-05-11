#pragma once

#include <cstdint>
#include <memory>

#include "driver/adc/interface.h"
#include "driver/config/interface.h"
#include "driver/factory/interface.h"

namespace driver::factory
{

class Stub final : public Interface 
{
public:
    
    explicit Stub() noexcept
    {}

    std::unique_ptr<adc::Interface> adc(config::Interface& config) noexcept override
    {
        return std::make_unique<adc::Stub>();
    }

    std::unique_ptr<gpio::Interface> gpio(config::Interface& config) noexcept override
    {
        return std::make_unique<gpio::Stub>();
    }

    std::unique_ptr<serial::Interface> serial(config::Interface& config) noexcept override
    {
        return std::make_unique<serial::Stub>();
    }

    std::unique_ptr<timer::Interface> timer(config::Interace& config) noexcept override
    {
        return std::make_unique<timer::Stub>();
    }

    std::unique_ptr<tempsensor::Interface> tempsensor(
            config::Interface& config,
            adc::Interface&
            ) noexcept override
    {
        return std::make_unique<tempsensor::Stub>();
    }

};
    
}
