#pragma once

#include <cstdint>
#include <cstring>
#include <iostream>

#include "driver/serial/interface.h"

namespace driver::serial
{
struct StubSettings final : public Settings{};

// Can be implemented as a static constant inside the class, see below.
static constexpr std::uint16_t BUF_SIZE{256U};

class Stub final : public Interface
{
public:
    explicit Stub()
    {
        std::cout << "Stub serial device created" << "\n";
    }

    bool initialize() noexcept override 
    {
	    initialized_ = true;
        const char* msg = "Serial initialized\n";
        write(msg);
        return initialized_;
    }

    void addData(const uint8_t* data, std::size_t len) noexcept
    {
	    if (nullptr == data) { return; }
	    auto bytesToAdd = std::min(len, sizeof(buf_));
	    std::memcpy(buf_, data, bytesToAdd);
	    bufLen_ = bytesToAdd;
        readPos_ = 0U;
    } 

    std::size_t readBytes(uint8_t* outBuf, std::size_t maxLen) noexcept override
    {
        if ((bufLen_ == 0U) or (outBuf == nullptr)) { return 0U; }
    
	    auto bytesToRead = std::min(maxLen, bufLen_);
        std::memcpy(outBuf, buf_ + readPos_, bytesToRead);
        readPos_ += bytesToRead;
        bufLen_ -= bytesToRead;
    
        if (bufLen_ == 0U) { readPos_ = 0U; }
        return bytesToRead;
    }

    const char* readString() noexcept override
    {
        if (bufLen_ == 0u) { return nullptr; }
        std::size_t index{0U};
        while (index < (sizeof(rxBuf_) - 1U))
        {
            std::uint8_t rxByte{0U};
            if (readBytes(&rxByte, 1U) == 0U) { break; }
            if ('\n' == rxByte or '\r' == rxByte) { break; }
            rxBuf_[index++] = rxByte;
        }
        rxBuf_[index] = '\0';
        return reinterpret_cast<const char*>(rxBuf_);
    }

    int write(std::uint8_t byte) noexcept override 
    {
        std::cout << (int)(byte);
        return 1;
    }

    int write(const char* msg) noexcept override
    {
        int i{0};
        for (; msg[i] != '\0'; ++i)
        {
            std::cout << msg[i];
        }
        return i;
    }

    bool isInitialized() const noexcept override
    {
        return initialized_;
    }

    std::size_t getAvailableData() const noexcept override
    {
        return bufLen_;
    }

    Stub(const Stub&) = delete;
    Stub(Stub&&) = delete;
    Stub& operator=(const Stub&) = delete;
    Stub& operator=(Stub&&) = delete;

private:
    // Constants can be implemented in a class, but they must be marked 'static', i.e.
    // shared between all instances of the class:
    static constexpr std::uint16_t BufSize{256U};

    bool initialized_{false}; 
    std::uint8_t rxBuf_[BUF_SIZE]{};
    std::uint8_t buf_[BUF_SIZE]{};
    std::size_t bufLen_{0U};
    std::uint16_t readPos_{0U};
};
} // namespace driver::serial
