//** GPIO-driver for the esp32s3. */
#pragma once

#include "driver/gpio/interface.h"
#include "driver/gpio.h"
#include "driver/gpio/mode.h"
#include <cstdint>

namespace driver::gpio
{

struct Esp32s3Settings final : public Settings
{
    std::uint8_t pin;
    Mode mode;
};                            

class Esp32s3 final : public Interface
{
public:
    explicit Esp32s3(const std::uint8_t pin, const Mode mode) noexcept;
    ~Esp32s3() noexcept;
    void on() noexcept override;
    void off() noexcept override;
    void toggle() noexcept override;
    bool read() const noexcept override;
private:
    const std::uint8_t myPin;
    const Mode myMode;

};

}// namespace driver::gpio
