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
    Save
}; 

struct Command
{
    /** Since the commands are at most 6 characters long we set the array size to 8 **/
    char cmd[8U];
    char args[2U][8U];
    std::size_t argCount;
};

}
