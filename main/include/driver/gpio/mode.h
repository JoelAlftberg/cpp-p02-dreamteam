/**
 * @brief GPIO mode definitions.
 */
#pragma once

#include <cstdint>

namespace driver::gpio
{
/**
 * @brief Enumeration of GPIO modes.
 */
enum class Mode : std::uint8_t
{
    Input,
    InputPullup,
    Output,
};
} // namespace driver::gpio
