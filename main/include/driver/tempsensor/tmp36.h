#pragma once

#include <cstdint>

// Try to sort headers alphabetically, especially if there is a lot of them.
#include "driver/adc/interface.h"
#include "driver/adc/types.h"
#include "driver/tempsensor/interface.h"

namespace driver::tempsensor
{
struct TMP36Settings final : public Settings{};

class Tmp36 final : public Interface 
{
public:
    explicit Tmp36(driver::adc::Interface& adc) noexcept;
    ~Tmp36() noexcept override;

    std::int16_t readCelsius() const noexcept override;
    void start() noexcept override;
    void stop() noexcept override;

    // Consider prohibiting copy and move semantics here.
private:
    driver::adc::Interface& myAdc;
    bool myState{false};
};
} // namespace driver::tempsensor
