/**
 * @brief Configuration settings for ESP32-S3.
 */
#pragma once

#include <cstdint>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/config/interface.h"

namespace driver::config
{
/**
 * @brief Configuration settings for ESP32-S3.
 */
class Esp32s3 final : public Interface
{
public:
    ~Esp32s3() noexcept override = default;

    void delay_ms(std::uint16_t ms) noexcept override
    {
        // Lägg i en cpp-fil och inkludera också freeRTOS.h och task.h där, se main.cpp
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
};
} // namespace driver::config
