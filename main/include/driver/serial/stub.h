#pragma once

#include <cstdint>
#include <cstring>
#include <strings.h>

#include "driver/serial/interface.h"

namespace driver::serial
{

static constexpr std::uint16_t BUF_SIZE{256U};

class Stub final : public Interface
{

public:

    bool initialize() noexcept override 
    {
	    initialized_ = true;
    }

    void addData(const uint8_t* data, std::size_t len) noexcept
    {
	    if (nullptr == data) { return; }
	    std::size_t bytesToAdd = std::min(len, sizeof(buf_);
	    std::memcpy(buf_, data, bytesToFeed);
	    bufLen_ = bytesToAdd;
        readPos_ = 0;
    } 

    std::size_t readBytes(uint8_t* outBuf, std::size_t maxLen) noexcept override
    {
        if (bufLen_ == 0 or outBuf == nullptr) { return 0; }
	    std::size_t bytesToRead = std::min(maxLen, bufLen_);
        std::memcpy(outBuf, buf_ + readPos_, bytesToRead);
        readPos_ += bytesToRead;
        bufLen_ -= bytesToRead;
        return bytesToRead;
    }

    const char* readString() noexcept override
    {
        if (bufLen_ == 0) { return nullptr; }
        std::size_t index{0U};
        while (index < sizeof(rxBuf_ - 1))
        {
            std::uint8_t rxByte{0U};
            if (readBytes(&rxByte, 1) == 0) { break; }
            if ('\n' == rxByte or '\r' == rxByte) { break; }
            rxBuf_[index++] = rxByte;
        }
        rxBuf_ = '\0';
        return reinterpret_cast<const char*>(rxBuf_);
    }


    int write(std::uint8_t byte) noexcept override 
    {
        std::cout << (int)(byte);
        return 1;
    }

    int write(const char* msg) noexcept override
    {
        std::int i{0U};
        for (; msg[i] != '\0'; ++i)
        {
            std::cout << msg[i];
        }
        return i;
    }

    bool isInitialized() const noexcept override
    {
        return isInitialized_;
    }

    Stub(const Stub&) = delete;
    Stub(Stub&&) = delete;
    Stub& operator=(const Stub&) = delete;
    Stub& operator=(Stub&&) = delete;

private:
    bool initialized_{false}; 
    std::uint8_t rxBuf_[BUF_SIZE]{};
    std::uint8_t buf_[BUF_SIZE]{};
    std::size_t bufLen_{0U};
    std::uint32_t baudRate_;
    std::uint16_t readPos_{0U};
};
}
