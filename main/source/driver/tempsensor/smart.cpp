#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/smart.h"
#include "driver/adc/interface.h"

#include "esp_log.h"

namespace driver::tempsensor
{
// -----------------------------------------------------------------------------
Smart::Smart(adc::Interface& adc, lin_reg::Interface& linReg) noexcept 
    :
    myAdc{adc},
    myLinReg{linReg},
    myState{false}
{}

// -----------------------------------------------------------------------------
// Can be set to default in the header only; no need to do it here (but completely fine,
// just more code to write for you). :)
Smart::~Smart() noexcept = default;

// -----------------------------------------------------------------------------
std::int16_t Smart::readCelsius() const noexcept
{
    if (!myState) { return 0; }

    // Vi predikterar temperaturen med inspänningen som input-data.
    // Modellen ska ha lärt sig att prediktera korrekt via träningen i main.cpp.
    const auto uin = myAdc.readVolt();
    const auto temp = myLinReg.predict(uin);

    // Remove this print; ESP_LOGI is ESP32-specific.
    return static_cast<std::int16_t>(temp + 0.5f);
}

// -----------------------------------------------------------------------------
void Smart::start() noexcept { myState = true; }

// -----------------------------------------------------------------------------
void Smart::stop() noexcept { myState = false; }

} // namespace driver::TMP36
