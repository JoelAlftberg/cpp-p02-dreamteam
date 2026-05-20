#pragma once

#include <cstddef>

namespace app::logic
{


enum class Commands 
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

CommandMapping commandTable[] =
{
    {"led", Commands::Led},
    {"blink", Commands::Blink},
    {"period", Commands::Period},
    {"temp", Commands::Temp},
    {"status", Commands::Status}
};

constexpr std::size_t CommandCount = sizeof(commandTable) / sizeof(commandTable[0]);

struct Command
{
    Commands command;
    char args[3U][16U];
    std::size_t argCount;
};

}
