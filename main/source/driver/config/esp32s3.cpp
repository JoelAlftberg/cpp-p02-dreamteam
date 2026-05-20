#include <cstddef>

#include "driver/config/esp32s3.h"
#include "driver/serial/esp32s3.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace driver::config
{

Esp32s3::Esp32s3() noexcept
{
    auto& led = gpioConfigs_[static_cast<std::size_t>(gpio::Id::LedYellow)];
    led.isEnabled = true;
    led.pin = 8U;
    led.mode = gpio::Mode::Output;

    led = gpioConfigs_[static_cast<std::size_t>(gpio::Id::LedBlue)];
    led.isEnabled = true;
    led.pin = 9U;
    led.mode = gpio::Mode::Output;

    auto& blinkTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::Blink)];
    blinkTimer.isEnabled = true;
    blinkTimer.timeout_ms = 1000U;

    auto& wifiLedTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::WifiLed)];
    wifiLedTimer.isEnabled = true;
    wifiLedTimer.timeout_ms = 1000U;    

    auto& temperatureAdc = adcConfigs_[static_cast<std::size_t>(adc::Id::Temperature)];
    temperatureAdc.isEnabled = true;
    temperatureAdc.pin = 11U;

    //serialConfig_.baudRate = 115200U;

}

void Esp32s3::delay_ms(std::uint16_t ms) noexcept 
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

const adc::Settings& Esp32s3::getADC(adc::Id id) const noexcept 
{
    return adcConfigs_[static_cast<std::size_t>(id)];
}

const gpio::Settings& Esp32s3::getGpio(gpio::Id id) const noexcept 
{
    return gpioConfigs_[static_cast<std::size_t>(id)];
}

const timer::Settings& Esp32s3::getTimer(timer::Id id) const noexcept 
{
    return timerConfigs_[static_cast<std::size_t>(id)];
}

const serial::Settings& Esp32s3::getSerial() const noexcept 
{
    return serialConfig_;
}

const tempsensor::Settings& Esp32s3::getTempsensor() const noexcept 
{
    return tempsensorConfig_;
}

} // namespace driver::config
