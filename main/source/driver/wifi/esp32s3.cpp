#include "driver/wifi/esp32s3.h"

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include <string.h>
#include <unistd.h>

namespace driver::wifi {

Esp32s3::Esp32s3(const char* ssid, const char* password) noexcept
    : mySsid{ssid}
    , myPassword{password}
    , connected{false}
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        (void)nvs_flash_erase();
        (void)nvs_flash_init();
    }

    esp_netif_init();

    esp_event_loop_create_default();

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
}

bool Esp32s3::connect() noexcept {
    wifi_config_t wifi_config = {};
    strncpy((char*)wifi_config.sta.ssid, mySsid, sizeof(wifi_config.sta.ssid));
    strncpy((char*)wifi_config.sta.password, myPassword, sizeof(wifi_config.sta.password));
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    if (esp_wifi_connect() != ESP_OK) return false;

    esp_netif_ip_info_t ip_info;
    esp_netif_t* netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    
    for (int i = 0; i < 100; i++) { 
        if (esp_netif_get_ip_info(netif, &ip_info) == ESP_OK && ip_info.ip.addr != 0) {
            connected = true;
            return true; 
        }
        usleep(100000);
    }

    return false;
}

bool Esp32s3::isConnected() const noexcept {
    return connected;
}

bool Esp32s3::disconnect() noexcept {
    if (esp_wifi_disconnect() == ESP_OK) {
        connected = false;
        return true;
    }
    return false;
}

Esp32s3::~Esp32s3() noexcept {
    esp_wifi_stop();
    esp_wifi_deinit();
}

} // namespace driver::wifi
