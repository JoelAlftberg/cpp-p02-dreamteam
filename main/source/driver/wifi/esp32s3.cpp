
// Consider using <cstring> instead.
#include <string.h>
#include <unistd.h>

#include "driver/wifi/esp32s3.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"

namespace driver::wifi
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(const char* ssid, const char* password) noexcept
    : mySsid{ssid}
    , myPassword{password}
    , connected{false}
{
    auto ret = nvs_flash_init();
    if ((ret == ESP_ERR_NVS_NO_FREE_PAGES) || (ret == ESP_ERR_NVS_NEW_VERSION_FOUND)) 
    {
        (void)nvs_flash_erase();
        (void)nvs_flash_init();
    }

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    auto cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept
{
    wifi_config_t wifi_config{};

    // Use std::strncpy if <cstring> is included.
    // Please us static_cast here instead of a C-style cast - they are similar, but
    // static_cast will warn/generate errors if something crazy is done.
    strncpy((char*)wifi_config.sta.ssid, mySsid, sizeof(wifi_config.sta.ssid));
    strncpy((char*)wifi_config.sta.password, myPassword, sizeof(wifi_config.sta.password));
    
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);    
    if (esp_wifi_connect() != ESP_OK) { return false; }

    esp_netif_ip_info_t ip_info{};
    auto* netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");

    constexpr std::uint8_t retries{100U};
    constexpr std::uint32_t delay_us{100000U};

    for (std::uint8_t i{}; i < retries; i++) 
    { 
        if ((esp_netif_get_ip_info(netif, &ip_info) == ESP_OK) && (ip_info.ip.addr != 0)) 
        {
            connected = true;
            return true; 
        }
        usleep(delay_us);
    }
    return false;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isConnected() const noexcept { return connected; }

bool Esp32s3::disconnect() noexcept 
{
    if (esp_wifi_disconnect() == ESP_OK) 
    {
        connected = false;
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept 
{
    esp_wifi_stop();
    esp_wifi_deinit();
}
} // namespace driver::wifi
