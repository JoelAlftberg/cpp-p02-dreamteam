#pragma once

#include <cstdint>

#include "driver/adc/interface.h"
#include "esp_adc/adc_oneshot.h"

namespace driver::adc
{

struct Esp32s3Settings final : public Settings
{
    std::uint8_t pin;
};

class Esp32s3 final : public Interface 
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] pin ADC pin. Must be withing range 0-7.
     */
    explicit Esp32s3(std::uint8_t pin) noexcept;

    ~Esp32s3() noexcept override;

    bool isInitialized() const noexcept override;
    
    std::uint16_t readRaw() const noexcept override;

    std::uint16_t readVolt() const noexcept override;

private:
    adc_oneshot_unit_handle_t myHandle;
    const adc_channel_t myChannel;
    bool myInitialized;
    
};
}
