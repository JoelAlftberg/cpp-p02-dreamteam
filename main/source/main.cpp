#include "app/logic/logic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "driver/config/esp32s3.h"
#include "driver/factory/esp32s3.h"

// -----------------------------------------------------------------------------
extern "C" void app_main(void)
{   
    auto config = std::make_unique<driver::config::Esp32s3>(); 
    auto factory = std::make_unique<driver::factory::Esp32s3>();

    app::logic::Logic logic{*factory, *config};
    logic.initialize();

    while (true)
    {
        logic.run();

        // To make this implementation truly platform independent, please add a delay method in
        // the config interface. If ESP32-S3 is used, this delay method should invoke the
        // 'vTaskDelay()' in the corresponding overridden method.
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
