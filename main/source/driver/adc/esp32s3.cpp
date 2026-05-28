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
constexpr adc_channel_t InvalidChannel{static_cast<adc_channel_t>(0x0FU)};
/**
 * @brief Converts a pin number to an ADC channel.
 * 
 * @param[in] pin ADC pin.
 * @return The corresponding ADC channel.
 */
adc_channel_t pinToChannel(std::uint8_t pin) {
    constexpr auto invalidChannel = static_cast<std::size_t>(InvalidChannel);
    constexpr std::size_t min{1U};
    constexpr std::size_t max{4U};
    const bool inRange{(min <= pin) && (max >= pin)};
    const std::size_t adcPin{inRange ? pin - 1U: invalidChannel};
    return static_cast<adc_channel_t>(adcPin);
}
} // namespace

/** Singleton ADC oneshot handle. */
adc_oneshot_unit_handle_t Esp32s3::myHandle{};

/**
 * @brief Constructor.
 * 
 * @param[in] pin ADC pin. Must be supported by ESP32-S3.
 */
Esp32s3::Esp32s3(std::uint8_t pin) noexcept 
    : myCaliHandle{}
    , myChannel{pinToChannel(pin)}
    , myInitialized{InvalidChannel != myChannel}
    {
        // Configure ADC if the channel is valid.
        if (myInitialized)
        {
            // Init oneshot.
            initOneshotHandle();
            adc_unit_t unit{ADC_UNIT_1};
            adc_oneshot_io_to_channel(static_cast<int>(pin), &unit, &myChannel);

            adc_oneshot_chan_cfg_t config{
                .atten = ADC_ATTEN_DB_12,
                .bitwidth = ADC_BITWIDTH_12
            };
            adc_oneshot_config_channel(myHandle, myChannel, &config);

            // 2. Initialize Calibration after adc_oneshot_config_channel
            adc_cali_curve_fitting_config_t caliConfig{
                .unit_id = ADC_UNIT_1,
                .chan = myChannel,
                .atten = ADC_ATTEN_DB_12,
                .bitwidth = ADC_BITWIDTH_12,
            };
            adc_cali_create_scheme_curve_fitting(&caliConfig, &myCaliHandle);
        }
    }
/**
 * @brief Destructor.
 * 
 */
 Esp32s3::~Esp32s3() noexcept{
    // Genomför cleanup; se till att frigöra resurser och hantera eventuella fel.
    if (myCaliHandle) { adc_cali_delete_scheme_curve_fitting(myCaliHandle); }
    return;
 }



/**
 * @brief Reads the ADC value.
 * 
 * @return The ADC value.
 */

std::uint16_t Esp32s3::readRaw() const noexcept {
    if (!myInitialized) { return 0U; }
    int raw{};
    adc_oneshot_read(myHandle, myChannel, &raw);
    return static_cast<std::uint16_t>(raw);
}

/**
 * @brief Reads the ADC value in volts.
 * 
 * @return The ADC value in volts (millivolts).
 */
std::uint16_t Esp32s3::readVolt() const noexcept
{
    const auto raw = static_cast<int>(readRaw());
    int voltage_mv{};
    adc_cali_raw_to_voltage(myCaliHandle, raw, &voltage_mv);
    return static_cast<std::uint16_t>(voltage_mv);
}

/**
 * @brief Checks the status of the ADC.
 * 
 * @return True if the ADC is initialized, false otherwise.
 */
bool Esp32s3::isInitialized() const noexcept {

    return myInitialized;
}

void Esp32s3::initOneshotHandle() noexcept
{
    static bool initialized{false};

    if (!initialized)
    {
        adc_oneshot_unit_init_cfg_t initCfg{};
        initCfg.unit_id = ADC_UNIT_1;
        adc_oneshot_new_unit(&initCfg, &myHandle);
        initialized = true;
    }
}

} // namespace driver::adc
