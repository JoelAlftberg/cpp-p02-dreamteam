#pragma once
#include <cstdint>
#include "driver/adc/interface.h"

namespace driver::adc{
class Stub final : public Interface {
public: 
    /**
 * @brief Constructor.
 * 
 * @param[in] pin ADC pin. Must be supported by ESP32-S3.
 */
    Stub() noexcept
        : myState{false}
        , myInput{0U}
    {
        std::printf("Stub ADC created.\n");
    }
/**
 * @brief Destructor.
 * 
 */


    ~Stub() noexcept {
        std::printf("Stub ADC destroyed.\n")
    }
    bool isInitialized() const noexcept override { 
        return myState;
    }

    std::uint16_t readRaw() const noexcept override { 
        // Pins are irrelevant for this stub, return simulated input.
        return myInput; 
    }

    std::uint16_t readVolt() const noexcept override { 
        return static_cast<std::uint16_t>((myInput / 4095.0) * 3300.0);
    }
    

    void simulateInput(std::uint16_t input) noexcept { 
        myInput = input;
    }
    Stub(const Stub&)                   = delete;
    Stub(Stub&&)                        = delete;
    Stub& operator = (const Stub&)      = delete;
    Stub& operator(Stub&&)              = delete;

private:
    bool myState;
    /** Simulated input. */
    std::uint16_t myInput;
};
} // namespace driver::adc

