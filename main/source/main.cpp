#include "app/logic/logic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "driver/config/esp32s3.h"
#include "driver/factory/esp32s3.h"

extern "C" void app_main(void)
{   
    auto config = std::make_unique<driver::config::Esp32s3>(); 
    auto factory = std::make_unique<driver::factory::Esp32s3>();

    app::logic::Logic logic{*factory, *config};
    
    logic.initialize();

    while (true)
    {
        logic.run();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
