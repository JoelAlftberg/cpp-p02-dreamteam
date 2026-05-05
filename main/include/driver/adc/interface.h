#pragma once

#include <cstdint>

namespace driver::adc{
class Interface{
public: 
    virtual ~Interface() noexcept = default;
    virtual bool isInitialized() const noexcept = 0;
    virtual std::uint16_t readRaw() const noexcept = 0;
    virtual std::uint16_t readVolt() const noexcept = 0;
};
} // namespace driver::adc
