#pragma once 

#include "esp_log.h"

#include "app/logic/interface.h"

#include "driver/common/utils.h"

#include "driver/adc/types.h"
#include "driver/gpio/types.h"
#include "driver/timer/types.h"

#include "driver/config/interface.h"
#include "driver/factory/interface.h"

#include "driver/adc/interface.h"
#include "driver/gpio/interface.h"
#include "driver/timer/interface.h"
#include "driver/serial/interface.h"
#include "driver/tempsensor/interface.h"
#include "driver/wifi/interface.h"
#include "driver/mqtt/interface.h"

#include <array>
#include <cstddef>
#include <cstring>
#include <memory>

using driver::utils::to_idx;

namespace app::logic
{

class Logic final : public Interface
{
public:

// -----------------------------------------------------------------------------
    explicit Logic(
            driver::factory::Interface& factory,
            driver::config::Interface& config
            ) noexcept 
    {
        const auto& ledSettings = config.getGpio(driver::gpio::Id::LedYellow);
        if (ledSettings.isEnabled)
        {
            const auto index = to_idx(driver::gpio::Id::LedYellow);
            gpios_[index] = factory.gpio(ledSettings);
        }

        const auto& wifiLedSettings = config.getGpio(driver::gpio::Id::LedBlue);
        if (wifiLedSettings.isEnabled)
        {
            const auto index = to_idx(driver::gpio::Id::LedBlue);
            gpios_[index] = factory.gpio(wifiLedSettings);
        }

        const auto& blinkTimerSettings = config.getTimer(driver::timer::Id::Blink);
        if (blinkTimerSettings.isEnabled)
        {
            const auto index = to_idx(driver::timer::Id::Blink);
            timers_[index] = factory.timer(blinkTimerSettings);
        }

        const auto& wifiLedTimerSettings = config.getTimer(driver::timer::Id::WifiLed);
        if (wifiLedTimerSettings.isEnabled)
        {
            const auto index = to_idx(driver::timer::Id::WifiLed);
            timers_[index] = factory.timer(wifiLedTimerSettings);
        }

        const auto& temperatureTimerSettings = config.getTimer(driver::timer::Id::Temperature);
        if (temperatureTimerSettings.isEnabled)
        {
            const auto index = to_idx(driver::timer::Id::Temperature);
            timers_[index] = factory.timer(temperatureTimerSettings);
        }

        const auto& temperatureAdcSettings = config.getADC(driver::adc::Id::Temperature);
        if (temperatureAdcSettings.isEnabled)
        {
            const auto index = to_idx(driver::adc::Id::Temperature);
            adcs_[index] = factory.adc(temperatureAdcSettings);
        }

        const auto& serialSettings = config.getSerial();
        serial_ = factory.serial(serialSettings);

        if (nullptr != adcs_[to_idx(driver::adc::Id::Temperature)])
        {
            driver::tempsensor::Settings tempsensorSettings{adcs_[to_idx(driver::adc::Id::Temperature)].get()};
            tempsensor_ = factory.tempsensor(tempsensorSettings);
        }
        
        const auto& wifiSettings = config.getWifi();
        wifi_ = factory.wifi(wifiSettings);        
        
        const auto& mqttSettings = config.getMQTT();
        mqtt_ = factory.mqtt(mqttSettings);
    }

// -----------------------------------------------------------------------------
    void initialize() noexcept 
    {
        auto& wifiLedTimer = timers_[to_idx(driver::timer::Id::WifiLed)];
        auto& temperatureTimer = timers_[to_idx(driver::timer::Id::Temperature)];

        wifi_->connect();
        mqtt_->startClient();
        wifiLedTimer->start();
        temperatureTimer->start();
        serial_->initialize();
        tempsensor_->start();
        
    }
 
// -----------------------------------------------------------------------------
    void run() noexcept override
    { 
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 
        auto& wifiLedTimer = timers_[to_idx(driver::timer::Id::WifiLed)];
        auto& temperatureTimer = timers_[to_idx(driver::timer::Id::Temperature)];
        auto& ledYellow = gpios_[to_idx(driver::gpio::Id::LedYellow)];
        auto& ledBlue = gpios_[to_idx(driver::gpio::Id::LedBlue)];

        (void) (temperatureTimer);
        
        
        blinkTimer->tick();
        wifiLedTimer->tick();
        temperatureTimer->tick();

        if (blinkTimer->hasTimedOut())
        {
            ledYellow->toggle();
        }

        if (wifi_->isConnected() && wifiLedTimer->hasTimedOut())
        {
            ledBlue->toggle();
        }

        if (temperatureTimer->hasTimedOut())
        {
            std::int16_t temperature = tempsensor_->readCelsius();
            char buf[8U];
            std::snprintf(buf, sizeof(buf), "%i", temperature);
            mqtt_->publish("dreamteam-p02/temperature", buf);
        }

        char incomingByte;
        while (serial_->readBytes(reinterpret_cast<uint8_t*>(&incomingByte), 1) > 0)
        {
            if (incomingByte == '\n' || incomingByte == '\r')
            {
                char printBuffer[80U];
                int bytesWritten = std::snprintf(printBuffer, sizeof(printBuffer), "Serial input received: %s\n", messageAccumulator_);
                
                if (bytesWritten >= static_cast<int>(sizeof(printBuffer)))
                {
                    std::memcpy(&printBuffer[sizeof(printBuffer) - 5], "...\n", 5);
                }
                
                serial_->write(printBuffer);

                Command cmd = parseCommand(messageAccumulator_);
                runCommand(cmd);
                messageLength_ = 0U;
                messageAccumulator_[messageLength_] = '\0';

            } 
            else if (incomingByte == '\b' || incomingByte == 127)
            {
                if (0U < messageLength_)
                {
                    messageLength_--;
                    messageAccumulator_[messageLength_] = '\0'; 
                }
            }
            else if (messageLength_ < (sizeof(messageAccumulator_) - 1U))
            { 
                messageAccumulator_[messageLength_++] = incomingByte;
                messageAccumulator_[messageLength_] = '\0';
            }
        }

        char mqttBuf[255]{};

        std::size_t bytesRead = mqtt_->receive(mqttBuf, sizeof(mqttBuf));
        if (bytesRead > 0)
        {
            Command cmd = parseCommand(mqttBuf);
            runCommand(cmd);
        }
    }
// -----------------------------------------------------------------------------
    bool isInitialized() const noexcept override
    {
        return true;
    }
// -----------------------------------------------------------------------------
    Command parseCommand(const char* input) noexcept override
    {
        Command cmd{};

        /* Tokenize the string on whitespace */
        char buffer[256];
        std::strncpy(buffer, input, sizeof(buffer) - 1);
        buffer[sizeof(buffer) -1] = '\0';

        const std::uint8_t MAX_TOKENS = 5;
        char* tokens[MAX_TOKENS];
        std::uint8_t token_count = 0;
        
        char* token = std::strtok(buffer, " ");
        
        while(nullptr != token && MAX_TOKENS != token_count)
        {
            tokens[token_count++] = token;
            token = std::strtok(nullptr, " ");
        }

        if (0 == token_count)
        {
            cmd.command = Commands::UNKNOWN;
        }

        bool foundCommand{false};

        for (std::size_t i = 0; i < CommandCount; ++i)
        {
            if (0 == std::strcmp(tokens[0], commandTable[i].str))
            {
                cmd.command = commandTable[i].cmd;
                foundCommand = true;
                break;
            }
        }
        
        if (!foundCommand) { cmd.command = Commands::UNKNOWN; }

        for (std::size_t j = 1; j < token_count && cmd.argCount < 2; j++)
        {
            std::strncpy(cmd.args[cmd.argCount], tokens[j], sizeof(cmd.args[0]) - 1);
            cmd.args[cmd.argCount][sizeof(cmd.args[0]) - 1] = '\0';
            cmd.argCount++;
        }
        
        return cmd;
    }
// -----------------------------------------------------------------------------
    void runCommand(Command cmd) noexcept override
    {
        auto& ledYellow = gpios_[to_idx(driver::gpio::Id::LedYellow)];
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 

        switch (cmd.command)
        {
            case Commands::Led:
            {
                if (blinkTimer->isRunning()) { break; }
                if (0 == std::strcmp("on", cmd.args[0]))
                {
                    ledYellow->on();
                }
                else if (0 == std::strcmp("off", cmd.args[0]))
                {
                    ledYellow->off();
                }
                break;
            }
            case Commands::Blink:
            {
                if (0 == std::strcmp("on", cmd.args[0]))
                {
                    blinkTimer->start();
                }
                else if (0 == std::strcmp("off", cmd.args[0]))
                {
                    blinkTimer->stop();
                    ledYellow->off();
                }
                break;
            }
            case Commands::Period:
            {
                char serialBuffer[80U];

                if (cmd.argCount < 1)
                {
                    std::snprintf(serialBuffer, sizeof(serialBuffer), "Error: Missing argument, please provide a time in milliseconds\n");
                    serial_->write(serialBuffer);
                    break;
                }

                char* endPtr = nullptr;

                std::uint32_t parsedPeriodMs = static_cast<std::uint32_t>(std::strtoul(cmd.args[0], &endPtr, 10));
                
                if (endPtr == cmd.args[0] || *endPtr != '\0')
                {
                    std::snprintf(serialBuffer, sizeof(serialBuffer), "Error: Argument was not a numerical value\n");
                    serial_->write(serialBuffer);
                    break;
                }

                blinkTimer->setTimeout(parsedPeriodMs);

                std::snprintf(serialBuffer, sizeof(serialBuffer), "Blink period set to %lu ms\n", parsedPeriodMs);
                serial_->write(serialBuffer);
                break;
            }
            case Commands::Temp:
            {
                std::int16_t temperatureReading = tempsensor_->readCelsius();

                char serialBuffer[80U];
                std::snprintf(serialBuffer, sizeof(serialBuffer), "Tempsensor reading: %u degrees Celsius\n", temperatureReading);
                serial_->write(serialBuffer);

                break;
            }
            case Commands::Status:
            {
                char statusBuffer[128U];
                const char* blinkStatus = (blinkTimer->isRunning() ? "on" : "off");
                std::uint32_t blinkPeriod = blinkTimer->getTimeout();
                std::int16_t temperature = tempsensor_->readCelsius();
                std::snprintf(statusBuffer, sizeof(statusBuffer), "--- Status ---\n - Blink: %s\n - Period: %lu ms\n - Temp: %i deg Celsius\n--------------\n", blinkStatus, blinkPeriod, temperature);
                serial_->write(statusBuffer);
                break;
            }
            default:
                break;
        }
    }

    Logic()                             = delete;
    Logic(const Logic&)                 = delete;
    Logic(Logic&&)                      = delete;
    Logic& operator=(const Logic&)      = delete;
    Logic& operator=(Logic&&)           = delete;

private:

    /* ADCs */
    std::array<std::unique_ptr<driver::adc::Interface>,
        static_cast<std::size_t>(driver::adc::Id::COUNT)> adcs_;

    /* GPIO pins */
    std::array<std::unique_ptr<driver::gpio::Interface>,
        static_cast<std::size_t>(driver::gpio::Id::COUNT)> gpios_;

    /* Timers */
    std::array<std::unique_ptr<driver::timer::Interface>,
        static_cast<std::size_t>(driver::timer::Id::COUNT)> timers_;

    /* Serial device used to read/write messages and commands */
    std::unique_ptr<driver::serial::Interface> serial_;

    /* Temperature sensor */
    std::unique_ptr<driver::tempsensor::Interface> tempsensor_;

    /* Wifi */
    std::unique_ptr<driver::wifi::Interface> wifi_;

    /* Mqtt */
    std::unique_ptr<driver::mqtt::Interface> mqtt_;

    /* Used for serial input */
    char messageAccumulator_[80U];
    std::size_t messageLength_ = 0U;
};

}
