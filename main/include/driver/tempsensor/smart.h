#pragma once

#include <cstdint>

#include "driver/tempsensor/interface.h"

// clang-format off
namespace ml::lin_reg { class Interface; }
namespace driver::adc { class Interface; }
// clang-format on

namespace driver::tempsensor
{
struct Esp32s3Settings final : public Settings{};                     

class Smart final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    explicit Smart(driver::adc::Interface& adc, ml::lin_reg::Interface& linReg) noexcept;

    /**
     * @brief Destructor.
     */
    ~Smart() noexcept override;

    std::int16_t readCelsius() const noexcept override;
    void start() noexcept override;
    void stop() noexcept override;

    Smart(const Smart&)           = delete;
    Smart(Smart&&)                = delete;
    Smart operator=(const Smart&) = delete;
    Smart& operator=(Smart&&)     = delete;

private:
    driver::adc::Interface& myAdc;
    ml::lin_reg::Interface& myLinReg;
    bool myState{false};


};
} // namespace driver::smart
