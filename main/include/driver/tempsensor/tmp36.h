#pragma once
#include <cstdint>
#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"

namespace driver::tempsensor{
class Tmp36 final : public Interface {
public:
    explicit Tmp36(driver::adc::Interface& adc) noexcept ;
    ~Tmp36() noexcept override;
    std::int16_t readCelsius() const noexcept override;
    void start() noexcept override;
    void stop() noexcept override;
private:
    driver::adc::Interface& myAdc;
    bool myState{false};

};
}
