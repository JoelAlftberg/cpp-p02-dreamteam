#include <cstdint>
#include <cstring>

#include "driver/serial/esp32s3.h"
#include "driver/uart.h"

namespace driver::serial
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(uart_config_t config, uart_port_t port, std::uint32_t baudRate) noexcept
    : config_{config}
    , port_{port}
    , baudRate_{baudRate}
{}

// -----------------------------------------------------------------------------
bool Esp32s3::initialize() noexcept
{
    esp_err_t initStatus{uart_driver_install(port_, RxBufSize, TxBufSize, 0U, nullptr, 0U)};
    if (ESP_OK != initStatus) { return false; }
    esp_err_t configStatus = uart_param_config(port_, &config_);

    setBaudRate(baudRate_);
    uart_set_pin(port_, 43U, 44U, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    initialized_ = (ESP_OK == configStatus  ? true : false);
    return initialized_;
}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{
    if (uart_is_driver_installed(port_))
    {
        uart_driver_delete(port_);
    }   
}

// -----------------------------------------------------------------------------
std::size_t Esp32s3::readBytes(uint8_t* dest, std::size_t maxLen) noexcept
{
    if (getAvailableData() == 0) { return 0; }
    auto bytesRead = uart_read_bytes(port_, dest, maxLen, 0);
    return (bytesRead > 0 ? static_cast<std::size_t>(bytesRead) : 0);
} 

// -----------------------------------------------------------------------------
const char* Esp32s3::readString() noexcept
{
    if (0U == getAvailableData()) { return nullptr; }
    std::size_t index{0U};

    while (index < (RxBufSize - 1U))
    {
        std::uint8_t rxByte{0U};

        if (readBytes(&rxByte, sizeof(rxByte)) == 0U) { break; }

        if ('\n' == rxByte or '\r' == rxByte) { break; }
        rxBuffer_[index++] = rxByte;
    }
    rxBuffer_[index] = '\0';
    return reinterpret_cast<const char*>(rxBuffer_);
}

// -----------------------------------------------------------------------------
int Esp32s3::write(std::uint8_t byte) noexcept
{
    return uart_write_bytes(port_, &byte, sizeof(byte));
}

// -----------------------------------------------------------------------------
int Esp32s3::write(const char* msg) noexcept
{
    if (nullptr == msg) { return -1; }
    const std::size_t msgLen{std::strlen(msg)};
    return uart_write_bytes(port_, msg, msgLen);
}

// -----------------------------------------------------------------------------
bool Esp32s3::isInitialized() const noexcept
{
    return initialized_;
}

// -----------------------------------------------------------------------------
std::size_t Esp32s3::getAvailableData() const noexcept
{
    std::size_t availableData{0U};
    if (uart_get_buffered_data_len(port_, &availableData) != ESP_OK) { return 0U; } 
    return availableData;
}

// -----------------------------------------------------------------------------
void Esp32s3::setBaudRate(std::uint32_t baudRate) noexcept
{
    baudRate_ = baudRate;
    uart_set_baudrate(port_ , baudRate_);
}
} // namespace driver::seria
