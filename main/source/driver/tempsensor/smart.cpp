#include <cstdint>
#include <cstdio>


#include "driver/tempsensor/smart.h"
#include "driver/adc/interface.h"
#include "driver/ml/lin_reg/interface.h"

namespace driver::tempsensor
{
// -----------------------------------------------------------------------------
Smart::Smart(adc::Interface& adc, ml::lin_reg::Interface& linReg) noexcept 
    : myAdc{adc},
      myLinReg{linReg},
      myState{false}
{}

// -----------------------------------------------------------------------------
std::int16_t Smart::readCelsius() const noexcept
{
    if (!myState) { return 0; }
    const auto uin  = myAdc.readVolt();
    const auto temp = myLinReg.predict(uin);
    return static_cast<std::int16_t>(temp + 0.5f);
}

// -----------------------------------------------------------------------------
void Smart::start() noexcept { myState = true; }

// -----------------------------------------------------------------------------
void Smart::stop() noexcept { myState = false; }

} // namespace driver::TMP36
