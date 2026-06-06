#pragma once

#include <cstddef>
#include <cstdint>

namespace app::logic
{
// Use std::uint8_t as underlying type => each enumerator allocates 1 byte of memory.
// By default int is used => 2-4 bytes per enumerator, most often 4.
enum class Commands : std::uint8_t
{
    Led,
    Blink,
    Period,
    Status,
    Temp,
    Save,
    UNKNOWN,
}; 

struct CommandMapping 
{
    const char* str;
    Commands cmd;
};

CommandMapping commandTable[]
{
    {"led", Commands::Led},
    {"blink", Commands::Blink},
    {"period", Commands::Period},
    {"temp", Commands::Temp},
    {"status", Commands::Status}
};

constexpr std::size_t CommandCount{sizeof(commandTable) / sizeof(commandTable[0U])};

struct Command
{
    // Try to avoid magic numbers by using constants, as shown here.
    static constexpr std::uint8_t CmdCount{3U};
    static constexpr std::uint8_t CmdLen{16U};
    Commands command;
    char args[CmdCount][CmdLen];
    std::size_t argCount; // Can be replaced with std::uint8_t to save space.
};
} // namespace app::logic
