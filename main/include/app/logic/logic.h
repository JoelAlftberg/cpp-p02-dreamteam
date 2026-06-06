#pragma once 

// Include standard headers first.
#include <array>
#include <cstddef>
#include <cstring>
#include <memory>

// Avoid esp headers in the system logic.
// If you need to print, use a serial driver, or at least something like std::printf or std::cout.
#include "esp_log.h"

#include "app/logic/interface.h"
#include "driver/adc/interface.h"
#include "driver/adc/types.h"
#include "driver/common/utils.h"
#include "driver/config/interface.h"
#include "driver/factory/interface.h"
#include "driver/gpio/interface.h"
#include "driver/gpio/types.h"
#include "driver/mqtt/interface.h"
#include "driver/serial/interface.h"
#include "driver/tempsensor/interface.h"
#include "driver/timer/interface.h"
#include "driver/timer/types.h"
#include "driver/wifi/interface.h"

// Avoid placing global using directives in headers, remember that all files where this header is 
// included will "inherit" this one, increasing the likehood of name collisions.
// Try to place them in a class or a namespace decreases the likehood dramatically.
// I would place these using directive inside the logic class, since it's only used there.
using driver::utils::to_idx;

namespace app::logic
{
// As mentioned to you in class, I suggest that you place the method definitions in a cpp file instead.
// Feel free to do this during the autumn (you will continue to work in your repo then, both
// for machine learning and for software- and hardware testing.
class Logic final : public Interface
{
    // The using directive can be placed here if it's only used inside the class.
    // Place it below 'public' to make it public.
    // using driver::utils::to_idx;
public:
    // -----------------------------------------------------------------------------
    explicit Logic(driver::factory::Interface& factory, driver::config::Interface& config) noexcept 
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

        // Remove this - you're using the temperatureTimer below => no need to ignore it.
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

            // Use constexpr instead of machine number '8U'.
            char buf[8U];
            std::snprintf(buf, sizeof(buf), "%i", temperature);
            mqtt_->publish("dreamteam-p02/temperature", buf);
        }

        // Feel free to use local variables for long lines with casts.
        char incomingByte{};
        auto* rxByte = reinterpret_cast<std::uint8_t*>(&incomingByte);
        
        while (serial_->readBytes(rxByte, sizeof(incomingByte)) > 0U)
        {
            if (incomingByte == '\n' || incomingByte == '\r')
            {
                // Avoid magic numbers.
                char printBuffer[80U]{};
                int bytesWritten = std::snprintf(printBuffer, sizeof(printBuffer), "Serial input received: %s\n", messageAccumulator_);
                
                if (bytesWritten >= static_cast<int>(sizeof(printBuffer)))
                {
                    constexpr auto bytesToCopy = 5U;
                    constexpr auto copyOffset  = sizeof(printBuffer) - bytesToCopy;
                    std::memcpy(&printBuffer[copyOffset], "...\n", bytesToCopy);
                }
                
                serial_->write(printBuffer);

                Command cmd = parseCommand(messageAccumulator_);
                runCommand(cmd);
                messageLength_ = 0U;
                messageAccumulator_[messageLength_] = '\0';

            } 
            // Magic numbers... I won't mention it again to avoid repeating myself. :)
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

        const auto bytesRead = mqtt_->receive(mqttBuf, sizeof(mqttBuf));
        if (bytesRead > 0)
        {
            Command cmd = parseCommand(mqttBuf);
            runCommand(cmd);
        }
    }

    // -----------------------------------------------------------------------------
    bool isInitialized() const noexcept override { return true; }

    // -----------------------------------------------------------------------------
    Command parseCommand(const char* input) noexcept override
    {
        // nullptr check?

        Command cmd{};

        /* Tokenize the string on whitespace */
        char buffer[256];
        std::strncpy(buffer, input, sizeof(buffer) - 1);
        buffer[sizeof(buffer) -1] = '\0';

        // Can/should be constexpr, not const => constexpr doesn't allocate memory.
        const std::uint8_t MAX_TOKENS = 5;
        char* tokens[MAX_TOKENS];
        std::uint8_t token_count = 0;
        
        char* token = std::strtok(buffer, " ");
        
        // Good practice: enclose conditions with parentheses => improves clarity and avoids
        // warnings about reliance on operator precedence, i.e. that != has higher priority than &&.
        while((nullptr != token) && (MAX_TOKENS != token_count))
        {
            tokens[token_count++] = token;
            token = std::strtok(nullptr, " ");
        }

        if (0U == token_count)
        {
            cmd.command = Commands::UNKNOWN;
        }

        bool foundCommand{false};

        for (std::size_t i{}; i < CommandCount; ++i)
        {
            if (0U == std::strcmp(tokens[0I], commandTable[i].str))
            {
                cmd.command = commandTable[i].cmd;
                foundCommand = true;
                break;
            }
        }
        
        if (!foundCommand) { cmd.command = Commands::UNKNOWN; }

        for (std::size_t j{1U}; (j < token_count) && (cmd.argCount < 2U); j++)
        {
            std::strncpy(cmd.args[cmd.argCount], tokens[j], sizeof(cmd.args[0U]) - 1U);
            cmd.args[cmd.argCount][sizeof(cmd.args[0U]) - 1U] = '\0';
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
                if (0U == std::strcmp("on", cmd.args[0U]))
                {
                    ledYellow->on();
                }
                else if (0U == std::strcmp("off", cmd.args[0U]))
                {
                    ledYellow->off();
                }
                break;
            }
            case Commands::Blink:
            {
                if (0U == std::strcmp("on", cmd.args[0U]))
                {
                    blinkTimer->start();
                }
                else if (0U == std::strcmp("off", cmd.args[0U]))
                {
                    blinkTimer->stop();
                    ledYellow->off();
                }
                break;
            }
            case Commands::Period:
            {
                char serialBuffer[80U];

                if (cmd.argCount < 1U)
                {
                    std::snprintf(serialBuffer, sizeof(serialBuffer), "Error: Missing argument, please provide a time in milliseconds\n");
                    serial_->write(serialBuffer);
                    break;
                }

                char* endPtr = nullptr;

                std::uint32_t parsedPeriodMs = static_cast<std::uint32_t>(std::strtoul(cmd.args[0U], &endPtr, 10));
                
                if (endPtr == cmd.args[0U] || *endPtr != '\0')
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

    // This alias could be used instead of the long array implementations below.
    template<typename T, auto Len>
    using DriverArray = std::array<std::unique_ptr<T>, static_cast<std::size_t>(Len)>;

    // Then you could write as follows:
    // DriverArray<driver::adc::Interface, driver::adc::Id::COUNT> adcs_;

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

    // I would add this constexpr above all the member variables instead of using a 
    // hardcoded '80' here.
    static constexpr std::uint8_t MsgLen{80U};
    char messageAccumulator_[MsgLen];

    std::size_t messageLength_ = 0U;
};
} // namespace app::logic
