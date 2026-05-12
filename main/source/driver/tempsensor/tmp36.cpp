#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/tmp36.h"
#include "driver/adc/interface.h"

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
    float voltage = static_cast<float>(myAdc.readVolt()) / 1000.0f;
    float temp = (voltage - 0.5f) * 100.0f;

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

