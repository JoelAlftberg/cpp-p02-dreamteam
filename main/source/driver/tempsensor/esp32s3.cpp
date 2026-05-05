#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/esp32s3.h"
#include "driver/tempsensor/interface.h"


namespace driver::tempsensor {

Esp32s3::Esp32s3() noexcept :
    handle{}
{
    constexpr int rangeMin{20};
    constexpr int rangeMax{50};
    temperature_sensor_config_t config{
        TEMPERATURE_SENSOR_CONFIG_DEFAULT(rangeMin, rangeMax)};
    temperature_sensor_install(&config, &handle);
    temperature_sensor_start(handle); 
}

Esp32s3::~Esp32s3() noexcept
{
    temperature_sensor_uninstall(handle);
}




std::int16_t Esp32s3::readCelsius() const noexcept
{
    float temp = 0.0f;

    // Check if sensor is started, if not return 0
    if (temperature_sensor_get_celsius(handle, &temp) != ESP_OK) {
        return 0;
    }
    // Round to nearest integer and convert to uint16_t
    return static_cast<std::int16_t>(temp + 0.5f);
}

void Esp32s3::start() noexcept
{
    temperature_sensor_start(handle);
}

void Esp32s3::stop() noexcept
{
    temperature_sensor_stop(handle);
}

} // namespace driver::tempsensor