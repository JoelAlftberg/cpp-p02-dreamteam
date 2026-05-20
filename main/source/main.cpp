#include "driver/factory/stub.h"
#include "driver/config/stub.h"
#include "app/logic/logic.h"
#include "driver/wifi/wifi.h"

#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "hal/uart_types.h"

#include <memory>
#include <iostream>
#include <string>
#include <future>


extern "C" void app_main(void)
{   
    driver::wifi::Esp32s3 wifi("goteborgfree", "");
    wifi.connect();
    auto config = std::make_unique<driver::config::Stub>(); 
    auto factory = std::make_unique<driver::factory::Stub>();

    app::logic::Logic logic{*factory, *config};
    
    logic.initialize();

    /** Used for simulating temp during development **/
    auto* tempsensorStub = factory->getTempsensorStub();
    tempsensorStub->simulatemyTemp(20);

    auto* serialStub = factory->getSerialStub();

    //--------------------------------------------------------------------
    /** UART stub testing **/
    uart_config_t uart_config ={};
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;


    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);
    //--------------------------------------------------------------------
    
    while (true)
    {
        std::uint8_t input;
        int len = uart_read_bytes(UART_NUM_0, &input, 1, 0);

        if (len > 0)
        {
            serialStub->addData(&input, 1);
        }

        logic.run();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
