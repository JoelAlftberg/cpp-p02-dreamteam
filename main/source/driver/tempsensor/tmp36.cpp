#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/tmp36.h"
#include "driver/adc/interface.h"

#include "esp_log.h"

namespace driver::tempsensor{

Tmp36::Tmp36(adc::Interface& adc) noexcept 
    :
      myAdc{adc},
      myState{false}
{
}

Tmp36::~Tmp36() noexcept = default;

std::int16_t Tmp36::readCelsius() const noexcept
{
    if (!myState) {
        return 0;
    }
    const float voltage = static_cast<float>(myAdc.readVolt()) / 1000.0f;
    const float temp = (voltage - 0.5f) * 100.0f;
    ESP_LOGI("TMP36", "Temperature: %f", temp);
    return static_cast<std::int16_t>(temp + 0.5f);
}

void Tmp36::start() noexcept
{
    myState = true;
}

void Tmp36::stop() noexcept
{
    myState = false;
}

} // namespace driver::TMP36

