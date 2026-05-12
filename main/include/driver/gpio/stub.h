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
        (void)myMode;
        std::printf("Initializing GPIO pin %u with mode %u\n", pin, static_cast<std::uint8_t>(mode));
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
