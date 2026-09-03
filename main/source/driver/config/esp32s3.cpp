#include <cstddef>

#include "driver/config/esp32s3.h"
#include "driver/serial/esp32s3.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"

namespace driver::config
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3() noexcept
{
    // I would've initialized the config member variables with an initializer list to be safe,
    // (to ensure that all members have been initialized), but you seem to have it under control
    // below, i.e., you initialize everything as far as I can tell.
    wifiConfig_.ssid = "goteborgfree";
    wifiConfig_.password = "";

    auto& ledYellow = gpioConfigs_[static_cast<std::size_t>(gpio::Id::LedYellow)];
    ledYellow.isEnabled = true;
    ledYellow.pin = 8U;
    ledYellow.mode = gpio::Mode::Output;

    auto& ledBlue = gpioConfigs_[static_cast<std::size_t>(gpio::Id::LedBlue)];
    ledBlue.isEnabled = true;
    ledBlue.pin = 9U;
    ledBlue.mode = gpio::Mode::Output;

    auto& blinkTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::Blink)];
    blinkTimer.isEnabled = true;
    blinkTimer.timeout_ms = 1000U;

    auto& wifiLedTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::WifiLed)];
    wifiLedTimer.isEnabled = true;
    wifiLedTimer.timeout_ms = 1000U;    

    auto& temperatureTimerSettings = timerConfigs_[static_cast<std::size_t>(timer::Id::Temperature)];
    temperatureTimerSettings.isEnabled = true;
    temperatureTimerSettings.timeout_ms = 1000U;

    auto& temperatureAdc = adcConfigs_[static_cast<std::size_t>(adc::Id::Temperature)];
    temperatureAdc.isEnabled = true;
    temperatureAdc.pin = 4U;

    uart_config_t config{};
    config.baud_rate = 115200U;
    config.data_bits = UART_DATA_8_BITS;
    config.parity = UART_PARITY_DISABLE;
    config.stop_bits = UART_STOP_BITS_1;
    config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

    serialConfig_.uart_config = config;
    serialConfig_.uart_port = UART_NUM_0;
    serialConfig_.baudRate = 115200U;

}

// -----------------------------------------------------------------------------
void Esp32s3::delay_ms(std::uint16_t ms) noexcept 
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

// -----------------------------------------------------------------------------
const adc::Settings& Esp32s3::getADC(adc::Id id) const noexcept 
{
    return adcConfigs_[static_cast<std::size_t>(id)];
}

// -----------------------------------------------------------------------------
const gpio::Settings& Esp32s3::getGpio(gpio::Id id) const noexcept 
{
    return gpioConfigs_[static_cast<std::size_t>(id)];
}

// -----------------------------------------------------------------------------
const timer::Settings& Esp32s3::getTimer(timer::Id id) const noexcept 
{
    return timerConfigs_[static_cast<std::size_t>(id)];
}

// -----------------------------------------------------------------------------
const serial::Settings& Esp32s3::getSerial() const noexcept 
{
    return serialConfig_;
}

// -----------------------------------------------------------------------------
const tempsensor::Settings& Esp32s3::getTempsensor() const noexcept 
{
    return tempsensorConfig_;
}

// -----------------------------------------------------------------------------
const wifi::Settings& Esp32s3::getWifi() const noexcept
{
    return wifiConfig_;
}

// -----------------------------------------------------------------------------
const mqtt::Settings& Esp32s3::getMQTT() const noexcept
{
    return mqttConfig_;
}
} // namespace driver::config
