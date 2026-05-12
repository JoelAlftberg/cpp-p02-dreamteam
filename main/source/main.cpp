#include "driver/factory/stub.h"
#include "driver/config/stub.h"
#include "app/logic/logic.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include <cstddef>
#include <memory>

extern "C" void app_main(void)
{
    auto config = std::make_unique<driver::config::Stub>(); 
    auto factory = std::make_unique<driver::factory::Stub>();

    app::logic::Logic logic{*factory, *config};

    logic.initialize();

    while (true)
    {
        logic.run();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
