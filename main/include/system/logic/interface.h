#pragma once 

namespace system::logic
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
    size_t argCount;

};


class Interface 
{
public:
    ~Interface() noexcept = default;

    virtual bool isInitialized() const noexcept = 0;

    virtual void run(const bool& stop) noexcept = 0;

    virtual Command parseCommand(const char* input) noexcept = 0;

    virtual void runCommand(Command cmd) noexcept = 0;
};

}
