/**
 * @brief GPIO interface.
 */
#pragma once

#include <cstdint>

namespace driver::gpio
{
/**
 * @brief GPIO interface.
 */
class Interface
{
public:
    virtual ~Interface() noexcept = default;
    virtual bool read() const noexcept = 0;
    virtual void on() noexcept = 0;
    virtual void off() noexcept = 0;
    virtual void toggle() noexcept = 0;
};
}// namespace driver::gpio
