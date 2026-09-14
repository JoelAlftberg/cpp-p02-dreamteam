#include "app/logic/logic.h"

#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

#include "driver/config/esp32s3.h"
#include "driver/factory/esp32s3.h"

#include "ml/lin_reg/adaptive.h"
#include "ml/types.h"

// -----------------------------------------------------------------------------
extern "C" void app_main(void)
{   
    constexpr std::size_t epochCount{1000U};

    const ml::Matrix trainIn{0.0, 1.0, 2.0};
    const ml::Matrix trainOut{2.0, 4.0, 6.0};
    ml::lin_reg::Adaptive linReg{trainIn, trainOut};

    // Vi tränar modellen innan vi kör resten av logiken. Om något går snett skriver vi ut ett felmeddelande och fastnar i en loop.
    if (!linReg.train(epochCount))
    {
        // Om ni vill, skriv ut ett felmeddelande här.

        while (1) {}
    }

    // Testa gärna att köra modellen, skriva gärna ut resultatet i terminalen med ESP_LOG:
    // Kör med trainIn som input (for const auto& input : trainIn) { ESP_LOG(); }
    // Input: 0.7 => output/temperature: 20 C.

    auto config = std::make_unique<driver::config::Esp32s3>();
    auto factory = std::make_unique<driver::factory::Esp32s3>();

    app::logic::Logic logic{*factory, *config, &linReg};
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
