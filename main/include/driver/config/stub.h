/**
 * @brief Configuration settings stub.
 */
#pragma once

#include <chrono>
#include <cstdint>
#include <thread>

#include "driver/config/interface.h"

namespace driver::config
{
/**
 * @brief Configuration settings for stub.
 */
class Stub final : public Interface
{
public:
    ~Stub() noexcept override = default;
    
    void delay_ms(std::uint16_t ms) noexcept override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
};
} // namespace driver::config
