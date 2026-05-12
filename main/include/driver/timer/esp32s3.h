#pragma once

#include <cstdint>

#include "driver/timer/interface.h"

namespace driver::timer
{
class Esp32s3 final : public Interface
{
public:
    explicit Esp32s3(const std::uint16_t timeout_ms) noexcept;

    ~Esp32s3() noexcept override = default;

    void start() noexcept override;

    void stop() noexcept override;

    bool isRunning() const noexcept override;

    bool hasTimedOut() noexcept override;

    void toggle() noexcept override;

    void tick() noexcept override;

    Esp32s3()                         = delete;
    Esp32s3(const Esp32s3&)           = delete;
    Esp32s3(Esp32s3&&)                = delete;
    Esp32s3 operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)     = delete;

private:
    void updateCounter() noexcept;

    const std::int64_t myTimeout_us;

    std::int64_t myCounter_us;

    std::int64_t myLastTime_us;
    
    bool myRunning;
};
}