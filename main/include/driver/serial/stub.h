#pragma once

#include <cstdint>

#include "driver/serial/interface.h"

namespace driver::serial
{

static constexpr std::uint8_t BUF_SIZE{64U};

class Stub final : public Interface
{

public:

    bool initialize() noexcept override;

    std::uint8_t read() const noexcept override {}

    const char* read() noexcept override {}

    void write(std::uint8_t) noexcept override {}

    void write(const char* msg) noexcept override {}

    bool isInitialized() const noexcept override {}

    bool isDataAvailable() const noexcept override {}

    void setBaudRate(std::uint32_t baudRate) noexcept {}

private:
    bool isConnected_;
    bool isInitialized_; 
    std::uint8_t buf_[BUF_SIZE];
    std::size_t bufLen;
    std::uint8_t* bufTail_;
    std::uint32_t baudRate;

};

}