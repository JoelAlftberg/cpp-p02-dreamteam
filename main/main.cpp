/**
 * @brief GPIO example.
 */
#include <cstdint>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief Blink an LED every 500 ms.
 */
extern "C" void app_main(void)
{
    constexpr gpio_num_t ledPin{static_cast<gpio_num_t>(2U)};
    constexpr std::uint32_t gpioHigh{1U};
    constexpr std::uint32_t gpioLow{0U};
    constexpr std::uint32_t blinkSpeed_ms{500U};

    // Configure LED as output.
    gpio_reset_pin(ledPin);
    gpio_set_direction(ledPin, GPIO_MODE_OUTPUT);

    // Blink LED every 500 ms.
    while (1)
    {
        gpio_set_level(ledPin, gpioHigh);
        ESP_LOGI("MAIN", "LED on!");
        vTaskDelay(pdMS_TO_TICKS(blinkSpeed_ms));

        gpio_set_level(ledPin, gpioLow);
        ESP_LOGI("MAIN", "LED off!");
        vTaskDelay(pdMS_TO_TICKS(blinkSpeed_ms));
    }
}
