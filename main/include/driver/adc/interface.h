#pragma once

#include "driver/factory/interface.h"

// Consider including standard headers first (just for structure).
#include <cstdint>

namespace driver::adc
{
struct Settings
{
    bool isEnabled = false; // Consider using {} instead of =.
};

class Interface
{
public: 
    virtual ~Interface() noexcept = default;
    virtual bool isInitialized() const noexcept = 0;
    virtual std::uint16_t readRaw() const noexcept = 0;
    virtual std::uint16_t readVolt() const noexcept = 0;
};
} // namespace driver::adc
