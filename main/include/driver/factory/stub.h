#pragma once

#include <cstdint>
#include <memory>

#include "driver/factory/interface.h"

namespace driver::factory
{

class Stub final : public Interface 
{
public:

    std::unique_ptr<adc::Interface> adc() noexcept override
    {
        return std::make_unique<adc::Stub>();
    }

    std::unique_ptr<gpio::Interface> gpio() noexcept override
    {
        return std::make_unique<gpio::Stub>();
    }

    std::unique_ptr<serial::Interface> serial() noexcept override
    {
        return std::make_unique<serial::Stub>();
    }

    std::unique_ptr<timer::Interface> timer() noexcept override
    {
        return std::make_unique<timer::Stub>();
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
