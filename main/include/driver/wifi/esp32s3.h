#pragma once

#include "driver/wifi/interface.h"
#include "esp_wifi.h"

namespace driver::wifi
{

struct Esp32s3Settings final : public Settings
{
    const char* ssid;
    const char* password;
};

class Esp32s3 final : public Interface
{
public:
    Esp32s3(const char* ssid, const char* password) noexcept;
    ~Esp32s3() noexcept;

    bool connect() noexcept override;
    bool disconnect() noexcept override;
    bool isConnected() const noexcept override;
private:
    const char* mySsid;
    const char* myPassword;
    bool connected;
};
}// namespace driver::wifi
