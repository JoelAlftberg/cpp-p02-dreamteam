#pragma once

#include <cstdint>
#include <cstdio>

#include "driver/gpio/interface.h"
#include "driver/gpio/mode.h"

namespace driver::gpio
{
struct StubSettings final : public Settings
{
    std::uint8_t pin;
    Mode mode;
};

class Stub final : public Interface
{
public:
    explicit Stub(const std::uint8_t pin, const Mode mode) noexcept
        : myPin{pin}
        , myMode{mode}
        , myState{false}
    {
        // No need to ignore myNode - only do this for input arguments.
        (void)myMode;

        // How about using a local constant for the cast?
        const auto modeId = static_cast<std::uint8_t>(mode);
        std::printf("Initializing GPIO pin %u with mode %u\n", pin, modeId);
    }

    ~Stub() noexcept override = default;

    void on() noexcept override
    {
        std::printf("Setting GPIO pin %u to HIGH\n", myPin);
        myState = true;
    }

    void off() noexcept override
    {
        std::printf("Setting GPIO pin %d to LOW\n", myPin);
        myState = false;
    }

    void toggle() noexcept override
    {
        std::printf("Toggling GPIO pin %d\n", myPin);
        myState = !myState;
    }

    bool read() const noexcept override
    {
        std::printf("Reading GPIO pin %d\n", myPin);
        return myState;
    }

    Stub()                       = delete; // No default constructor.
    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    const std::uint8_t myPin;
    const Mode myMode;
    bool myState;
};
} // namespace driver::gpio
