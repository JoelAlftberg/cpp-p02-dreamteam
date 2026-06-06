#pragma once

#include <cstdint>

namespace driver::gpio {

// Please use uint8_t for your enums => you ensure that a variable of this enum class will only
// allocate one byte. By default, an enum will be interpreted as an int and will allocate four
// bytes on most systems.
enum class Id : std::uint8_t
{
    LedYellow,
    LedBlue,
    LedRed,
    COUNT // This needs to always be the last entry of the enum
    // Again, I would name this Count.
};
} // namespace driver::gpio
