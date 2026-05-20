#pragma once

#include "esp_wifi.h"

namespace driver::wifi
{
class Esp32s3
{
public:
    Esp32s3(const char* ssid, const char* password) noexcept;
    ~Esp32s3() noexcept;

    bool connect() noexcept;
    bool disconnect() noexcept;
    bool isConnected() const noexcept;
private:
    const char* mySsid;
    const char* myPassword;
    bool connected;
};
}// namespace driver::wifi