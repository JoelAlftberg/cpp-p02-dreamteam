/**
 * @brief Configuration settings for ESP32-S3.
 */
#pragma once

#include <cstdint>
#include <array>

#include "driver/mqtt/esp32s3.h"
#include "driver/mqtt/interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/adc/esp32s3.h"
#include "driver/gpio/esp32s3.h"
#include "driver/timer/esp32s3.h"
#include "driver/serial/esp32s3.h"
#include "driver/tempsensor/esp32s3.h"
#include "driver/wifi/esp32s3.h"

#include "driver/config/interface.h"


namespace driver::config
{
/**
 * @brief Configuration settings for ESP32-S3.
 */
class Esp32s3 final : public Interface
{
public:

    Esp32s3() noexcept;
    
    ~Esp32s3() noexcept override = default;

    void delay_ms(std::uint16_t ms) noexcept override;
    
    const adc::Settings& getADC(adc::Id id) const noexcept override;

    const gpio::Settings& getGpio(gpio::Id id) const noexcept override;

    const timer::Settings& getTimer(timer::Id id) const noexcept override; 

    const serial::Settings& getSerial() const noexcept override;

    const tempsensor::Settings& getTempsensor() const noexcept override;

    const wifi::Settings& getWifi() const noexcept;

private:
    std::array<adc::Esp32s3Settings, static_cast<std::size_t>(adc::Id::COUNT)> adcConfigs_; 
    std::array<gpio::Esp32s3Settings, static_cast<std::size_t>(gpio::Id::COUNT)> gpioConfigs_; 
    std::array<timer::Esp32s3Settings, static_cast<std::size_t>(timer::Id::COUNT)> timerConfigs_; 
    serial::Esp32s3Settings serialConfig_;
    tempsensor::Settings tempsensorConfig_; 
    wifi::Esp32s3Settings wifiConfig_;
    mqtt::Esp32s3Settings mqttConfig_;
};
} // namespace driver::config
