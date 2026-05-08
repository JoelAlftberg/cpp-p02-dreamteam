/**
 * @brief Configuration interface.
 */
#pragma once

#include <cstdint>

namespace driver::config
{
/**
 * @brief Configuration interface.
 */
class Interface
{
public:
    virtual ~Interface() noexcept = default;
    virtual void delay_ms(std::uint16_t ms) noexcept = 0;
};
} // namespace driver::config
