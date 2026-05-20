/**
 * @brief Configuration settings for ESP32-S3.
 */
#pragma once

#include <cstdint>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/config/interface.h"

namespace driver::config
{
/**
 * @brief Configuration settings for ESP32-S3.
 */
class Esp32s3 final : public Interface
{
public:
    ~Esp32s3() noexcept override = default;

    void delay_ms(std::uint16_t ms) noexcept override
    {
        // Lägg i en cpp-fil och inkludera också freeRTOS.h och task.h där, se main.cpp
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
    const adc::Settings& getADC(adc::Id id) const noexcept override;

    const gpio::Settings& getGpio(gpio::Id id) const noexcept override;

    const timer::Settings& getTimer(timer::Id id) const noexcept override; 

    const serial::Settings& getSerial() const noexcept override;

    const tempsensor::Settings& getTempsensor() const noexcept override;

private:
    std::array<adc::Esp32s3Settings, static_cast<std::size_t>(adc::Id::COUNT)> adcConfigs_; 
    std::array<gpio::Esp32s3Settings, static_cast<std::size_t>(gpio::Id::COUNT)> gpioConfigs_; 
    std::array<timer::Esp32s3Settings, static_cast<std::size_t>(timer::Id::COUNT)> timerConfigs_; 
    serial::Esp32s3Settings serialConfig_;
    tempsensor::Esp32s3Settings tempsensorConfig_; 
};
} // namespace driver::config
