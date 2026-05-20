#pragma once 

#include "app/logic/commands.h"

namespace app::logic
{

class Interface 
{
public:
    ~Interface() noexcept = default;

    virtual bool isInitialized() const noexcept = 0; 

    virtual void run() noexcept = 0;

    virtual Command parseCommand(const char* input) noexcept = 0;

    virtual void runCommand(Command cmd) noexcept = 0;
};

}
