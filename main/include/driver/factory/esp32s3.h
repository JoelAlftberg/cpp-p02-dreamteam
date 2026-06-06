#pragma once

#include <cstdint>
#include <memory>

#include "driver/serial/interface.h"
#include "driver/factory/interface.h"
#include "driver/adc/esp32s3.h"
#include "driver/config/esp32s3.h"
#include "driver/gpio/esp32s3.h"
#include "driver/tempsensor/tmp36.h"
#include "driver/timer/esp32s3.h"
#include "driver/mqtt/esp32s3.h"
#include "driver/wifi/esp32s3.h"

namespace driver::factory
{
// I would consider defining the factory methods inside a cpp file, even though they're quite small.
// However, I do think that it's completely fine to define them here. Here I'm like 60/40 in favor
// of placing them in a cpp file.
class Esp32s3 final : public Interface 
{
public:
    Esp32s3() noexcept = default;

    // I would've added a default destructor for clarity, but it's fine; the compiler will
    // generate one for you if you don't add one.

    std::unique_ptr<adc::Interface> adc(const adc::Settings& settings) const noexcept override
    {
        const auto& adcSettings = static_cast<const adc::Esp32s3Settings&>(settings);
        return std::make_unique<adc::Esp32s3>(adcSettings.pin);
    }

    std::unique_ptr<gpio::Interface> gpio(const gpio::Settings& settings) const noexcept override
    {
        const auto& gpioSettings = static_cast<const gpio::Esp32s3Settings&>(settings);
        return std::make_unique<gpio::Esp32s3>(gpioSettings.pin, gpioSettings.mode);
    }
    
    std::unique_ptr<serial::Interface> serial(const serial::Settings& settings) noexcept override
    {
        const auto& serialSettings = static_cast<const serial::Esp32s3Settings&>(settings);
        return std::make_unique<serial::Esp32s3>(serialSettings.uart_config, serialSettings.uart_port, serialSettings.baudRate);
    }

    std::unique_ptr<timer::Interface> timer(const timer::Settings& settings) const noexcept override
    {
        const auto& timerSettings = static_cast<const timer::Esp32s3Settings&>(settings);
        return std::make_unique<timer::Esp32s3>(timerSettings.timeout_ms);
    }

    std::unique_ptr<tempsensor::Interface> tempsensor(const tempsensor::Settings& settings) noexcept override
    {
        return std::make_unique<tempsensor::Tmp36>(*settings.adc);
    }

    std::unique_ptr<wifi::Interface> wifi(const wifi::Settings& settings) const noexcept override
    {
        const auto& wifiSettings = static_cast<const wifi::Esp32s3Settings&>(settings);
        return std::make_unique<wifi::Esp32s3>(wifiSettings.ssid, wifiSettings.password);
    }

    std::unique_ptr<mqtt::Interface> mqtt(const mqtt::Settings& settings) const noexcept override
    {
        return std::make_unique<mqtt::Esp32s3>(nullptr);
    }

    // I would delete copy and move constructors, as well as the corresponding assignment operators,
    // unless you indent to support the operations for this class.
};
} // namespace driver::factory
