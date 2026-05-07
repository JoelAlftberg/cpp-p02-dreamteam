// Standard headers.
#include <cstdint>
#include <cstdio>

// ESP32-specific headers.
#include <driver/adc/esp32s3.h>
#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_continuous.h>
#include <esp_adc/adc_cali.h>
#include <esp_adc/adc_cali_scheme.h>
#include <hal/adc_types.h>
#include <sdkconfig.h>

// Local headers.
#include "driver/adc/esp32s3.h"
#include "driver/adc/interface.h"

namespace driver::adc{

namespace
{
constexpr adc_channel_t InvalidChannel{static_cast<adc_channel_t>(0xFFU)};
} // namespace
/**
 * @brief Converts a pin number to an ADC channel.
 * 
 * @param[in] pin ADC pin.
 * @return The corresponding ADC channel.
 */
static adc_channel_t pinToChannel(std::uint8_t pin) {
    switch (pin)
    {
        case 0:
            return ADC_CHANNEL_0;
        case 1:
            return ADC_CHANNEL_1;
        case 2:
            return ADC_CHANNEL_2;
        case 3:
            return ADC_CHANNEL_3;
        case 4:
            return ADC_CHANNEL_4;
        case 5:
            return ADC_CHANNEL_5;
        case 6:
            return ADC_CHANNEL_6;
        case 7:
            return ADC_CHANNEL_7;
        default:
            return InvalidChannel;
    }
    
}

/**
 * @brief Constructor.
 * 
 * @param[in] pin ADC pin. Must be supported by ESP32-S3.
 */
Esp32s3::Esp32s3(std::uint8_t pin) noexcept 
    : myHandle{}
    , myChannel{pinToChannel(pin)}
    , myInitialized{InvalidChannel != myChannel}
    {
        // Configure ADC if the channel is valid.
        if (myInitialized)
        {
            adc_oneshot_unit_init_cfg_t initCfg{};
            initCfg.unit_id = ADC_UNIT_1;
            adc_oneshot_new_unit(&initCfg, &myHandle);

            adc_oneshot_chan_cfg_t config{
                .atten = ADC_ATTEN_DB_12,
                .bitwidth = ADC_BITWIDTH_12
            };
            adc_oneshot_config_channel(myHandle, myChannel, &config);
        }
    }
/**
 * @brief Destructor.
 * 
 */
 Esp32s3::~Esp32s3() noexcept{
    // Genomför cleanup; se till att frigöra resurser och hantera eventuella fel.
    adc_oneshot_del_unit(myHandle);
    return;
 }



/**
 * @brief Reads the ADC value.
 * 
 * @return The ADC value.
 */

std::uint16_t Esp32s3::readRaw() const noexcept {
    if (!myInitialized) { return 0U; }
    int value{};
    adc_oneshot_read(myHandle, myChannel, &value);
    return static_cast<std::uint16_t>(value);
}
/**
 * @brief Reads the ADC value in volts.
 * 
 * @return The ADC value in volts (millivolts).
 */
std::uint16_t Esp32s3::readVolt() const noexcept
{
    std::uint16_t raw = readRaw();
    return static_cast<std::uint16_t>((raw / 4095.0f) * 3300.0f);
}
/**
 * @brief Checks the status of the ADC.
 * 
 * @return True if the ADC is initialized, false otherwise.
 */
bool Esp32s3::isInitialized() const noexcept {

    return myInitialized;
}

} // namespace driver::adc
