#pragma once

#include <cstdint>

#include "driver/adc/interface.h"

namespace driver::tempsensor
{
struct Settings
{
    driver::adc::Interface* adc;
};

class Interface
{
public: 
    virtual ~Interface() noexcept = default;
    virtual std::int16_t readCelsius() const noexcept = 0;
    virtual void start() noexcept = 0;
    virtual void stop() noexcept = 0;
};
} // namespace driver::tempsensor
