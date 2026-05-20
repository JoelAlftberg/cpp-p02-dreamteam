#pragma once 

#include <cstdint>

namespace driver::serial
{

struct Settings
{

};

class Interface
{

public:
    virtual ~Interface() noexcept = default;

    virtual bool initialize() noexcept = 0;
    
    virtual std::size_t readBytes(uint8_t* outBuf, std::size_t maxLen) noexcept = 0;

    virtual const char* readString() noexcept = 0;

    virtual int write(std::uint8_t) noexcept = 0;

    virtual int write(const char* msg) noexcept = 0;

    virtual bool isInitialized() const noexcept = 0;

    virtual std::size_t getAvailableData() const noexcept = 0;

private:

};

} // namespace driver::serial

