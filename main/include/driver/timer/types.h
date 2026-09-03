#pragma once

#include <cstdint>

namespace driver::timer 
{
// Set the underlying type to uint8_t => the enumerators only allocated 1 byte instead of 4.
enum class Id : std::uint8_t
{
    Blink,
    Temperature,
    WifiLed,
    COUNT // Count
};
} // namespace driver::timer
