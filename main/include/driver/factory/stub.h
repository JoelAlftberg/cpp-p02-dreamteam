#pragma once

#include <cstdint>
#include <memory>

#include "driver/factory/interface.h"

#include "driver/adc/stub.h"
#include "driver/gpio/stub.h"
#include "driver/serial/stub.h"
#include "driver/timer/stub.h"
#include "driver/tempsensor/stub.h"

namespace driver::factory
{
class Stub final : public Interface 
{
public:
    // Consider using '= default' instead of '{}' here.
    // No need to mark a default constructor explicit, but it doesn't hurt. :)
    explicit Stub() noexcept
    {}

    std::unique_ptr<adc::Interface> adc(const adc::Settings& settings) const noexcept override
    {
        return std::make_unique<adc::Stub>();
    }

    std::unique_ptr<gpio::Interface> gpio(const gpio::Settings& settings) const noexcept override
    {
        const auto& gpioSettings = static_cast<const gpio::StubSettings&>(settings);
        return std::make_unique<gpio::Stub>(gpioSettings.pin, gpioSettings.mode);
    }

    std::unique_ptr<serial::Interface> serial(const serial::Settings& settings) noexcept override
    {
        // Nice way to return a smart pointer as well as keeping a reference (in the shape of a
        // raw pointer) here. The unique pointer is owned by the caller, but you can still access
        // it from here. Just make sure that serialStub_ isn't nullptr before usage (in case the
        // unique pointer has been deleted).
        auto stub = std::make_unique<serial::Stub>(); 
        serialStub_ = stub.get();
        return stub;
    }

    std::unique_ptr<timer::Interface> timer(const timer::Settings& settings) const noexcept override
    {
        const auto& timerSettings = static_cast<const timer::StubSettings&>(settings);
        return std::make_unique<timer::Stub>(timerSettings.timeout_ms);
    }

    std::unique_ptr<tempsensor::Interface> tempsensor(
        const tempsensor::Settings& settings) noexcept override
    {
        auto stub = std::make_unique<tempsensor::Stub>();
        tempsensorStub_ = stub.get();
        return stub;     
    }

    tempsensor::Stub* getTempsensorStub() const
    {
        return tempsensorStub_;
    }

    serial::Stub* getSerialStub() const
    {
        return serialStub_;
    }

private:
    tempsensor::Stub* tempsensorStub_{nullptr};
    serial::Stub* serialStub_{nullptr};
};
} // namespace driver::factory
