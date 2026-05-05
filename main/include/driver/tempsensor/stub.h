#pragma once
#include <cstdint>
#include <cstdio>
#include "driver/tempsensor/interface.h"

namespace driver::tempsensor{
class Stub final : public Interface {
public:
    Stub() noexcept
        : status{false},
        temp{0U}
    {
        std::printf("Stub temperature sensor created.\n");
    }

    ~Stub() noexcept override
    {
        std::printf("Stub temperature sensor destroyed.\n");
    }
   
    std::int16_t readCelsius() const noexcept {
        return temp;

    }
    void start() noexcept {
        status = true;

    }
    void stop() noexcept {
        status = false;

    }
 
    Stub(const Stub&)                   = delete;
    Stub(Stub&&)                        = delete;
    Stub& operator=(const Stub&)        = delete;
    Stub& operator=(Stub&&)             = delete;

private:
    bool status;
    std::uint16_t temp;
};
} // namespace driver::tempsensor