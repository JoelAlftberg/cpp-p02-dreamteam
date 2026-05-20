#include <cstddef>
#include <thread>
#include <chrono>

#include "driver/config/stub.h"
#include "driver/serial/stub.h"

namespace driver::config
{

Stub::Stub() noexcept
{
    auto& led = gpioConfigs_[static_cast<std::size_t>(gpio::Id::LedYellow)];
    led.isEnabled = true;
    led.pin = 8U;
    led.mode = gpio::Mode::Output;

    auto& blinkTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::Blink)];
    blinkTimer.isEnabled = true;
    blinkTimer.timeout_ms = 1000U;

    auto& temperatureTimer = timerConfigs_[static_cast<std::size_t>(timer::Id::Temperature)];
    temperatureTimer.isEnabled = true;
    temperatureTimer.timeout_ms = 500U;

}

void Stub::delay_ms(std::uint16_t ms) noexcept 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

const adc::Settings& Stub::getADC(adc::Id id) const noexcept 
{
    return adcConfigs_[static_cast<std::size_t>(id)];
}

const gpio::Settings& Stub::getGpio(gpio::Id id) const noexcept 
{
    return gpioConfigs_[static_cast<std::size_t>(id)];
}

const timer::Settings& Stub::getTimer(timer::Id id) const noexcept 
{
    return timerConfigs_[static_cast<std::size_t>(id)];
}

const serial::Settings& Stub::getSerial() const noexcept 
{
    return serialConfig_;
}

const tempsensor::Settings& Stub::getTempsensor() const noexcept 
{
    return tempsensorConfig_;
}

} // namespace driver::config
