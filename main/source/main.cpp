#include "app/logic/logic.h"
#include "driver/wifi/wifi.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "driver/config/esp32s3.h"
#include "driver/factory/esp32s3.h"

extern "C" void app_main(void)
{   
    //driver::wifi::Esp32s3 wifi("goteborgfree", "");
    //wifi.connect();

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
