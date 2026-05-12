#pragma once
#include <cstdint>

namespace driver::tempsensor{
class Interface{
public: 
    virtual ~Interface() noexcept = default;
    virtual std::int16_t readCelsius() const noexcept = 0;
    virtual void start() noexcept = 0;
    virtual void stop() noexcept = 0;


};
} // namespace driver::tempsensor
