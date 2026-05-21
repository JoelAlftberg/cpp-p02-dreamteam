#pragma once

#include <cstdint>

#include "driver/serial/interface.h"
#include "driver/uart.h"

namespace driver::serial
{

struct Esp32s3Settings : public Settings
{
    uart_config_t   uart_config;
    uart_port_t     uart_port;
    std::uint32_t   baudRate;
};

static constexpr std::size_t RxBufSize{256U};
static constexpr std::size_t TxBufSize{256U};

class Esp32s3 final : public Interface
{

public:

    explicit Esp32s3(uart_config_t config, uart_port_t port, std::uint32_t baudRate) noexcept;

    ~Esp32s3() noexcept;
    
    bool initialize() noexcept override;
    
    std::size_t readBytes(uint8_t* dest, std::size_t maxLen) noexcept override;

    const char* readString() noexcept override;

    int write(std::uint8_t) noexcept override;

    int write(const char* msg) noexcept override;

    bool isInitialized() const noexcept override;

    std::size_t getAvailableData() const noexcept override;

    void setBaudRate(std::uint32_t baudRate) noexcept; 

private:
    uart_config_t config_{};
    uart_port_t port_;
    std::uint32_t baudRate_;
    std::uint8_t rxBuffer_[RxBufSize]{};
    bool initialized_;
    
};
}
