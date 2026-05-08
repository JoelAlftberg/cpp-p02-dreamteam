#include <cstdint>
#include "driver/gpio/esp32s3.h"
#include "driver/timer/esp32s3.h"
#include "driver/timer/interface.h"
#include "driver/gpio/interface.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{
    driver::gpio::Esp32s3 led{2U, driver::gpio::Mode::Output};
    driver::timer::Esp32s3 timer{1000};
    timer.start();
    led.on();

    ESP_LOGI("main", "Starting timer!"); 
    ESP_LOGI("main", "Enable LED!");

    while (true)
    {
        constexpr std::uint32_t loopDelay_ms{10U};

        if (timer.hasTimedOut()) 
        {
            ESP_LOGI("main", "LED toggled!"); 
            led.toggle(); 

            // Reset the watchdog indirectly.
            // Later; use generic delay function, which calls this function if we're using ESP32-drivers.
            vTaskDelay(pdMS_TO_TICKS(loopDelay_ms));
        }
    }

}
