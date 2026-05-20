#pragma once 

#include "app/logic/interface.h"

#include "driver/common/utils.h"

#include "driver/adc/types.h"
#include "driver/gpio/types.h"
#include "driver/timer/types.h"

#include "driver/config/interface.h"
#include "driver/factory/interface.h"

#include <array>
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <string>

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

        const auto& blinkTimerSettings = config.getTimer(driver::timer::Id::Blink);
        if (blinkTimerSettings.isEnabled) {
            const auto index = to_idx(driver::timer::Id::Blink);
            timers_[index] = factory.timer(blinkTimerSettings);
        }

        const auto& tempTimerSettings = config.getTimer(driver::timer::Id::Temperature);
        if (tempTimerSettings.isEnabled)
        {
            const auto index = to_idx(driver::timer::Id::Temperature);
            timers_[index] = factory.timer(tempTimerSettings);
        }

        const auto& serialSettings = config.getSerial();
        serial_ = factory.serial(serialSettings);

        const auto& tempsensorSettings = config.getTempsensor();
        tempsensor_ = factory.tempsensor(tempsensorSettings);
        
    }

// -----------------------------------------------------------------------------
    void initialize() noexcept 
    {
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 
        if (blinkTimer)
        {
            blinkTimer->start();
        }

        auto& temperatureTimer = timers_[to_idx(driver::timer::Id::Temperature)]; 
        if (temperatureTimer)
        {
            temperatureTimer->start();
        }

        auto& led = gpios_[to_idx(driver::gpio::Id::LedYellow)];
        if (led)
        {
            led->on();
        }

        serial_->initialize();
        tempsensor_->start();
    }
 
// -----------------------------------------------------------------------------
    void run() noexcept override
    { 
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 
        auto& temperatureTimer = timers_[to_idx(driver::timer::Id::Temperature)];
        auto& ledYellow = gpios_[to_idx(driver::gpio::Id::LedYellow)];

        blinkTimer->tick();
        temperatureTimer->tick();

        if(blinkTimer->hasTimedOut())
        {
            ledYellow->toggle();
        }
        
        if(temperatureTimer->hasTimedOut())
        {
            std::int16_t temperatureReading = tempsensor_->readCelsius();
            std::string temperatureString = std::format("Tempsensor reading: {}\n", temperatureReading);
            serial_->write(temperatureString.c_str());
        }

        char incomingByte;
        while (serial_->readBytes(reinterpret_cast<uint8_t*>(&incomingByte), 1) > 0)
        {
            if (incomingByte == '\n' or incomingByte == '\r')
            {
                std::cout << "Logic: Command recieved: " << messageAccumulator_.c_str() << "\n";
                Command cmd = parseCommand(messageAccumulator_.c_str());
                runCommand(cmd);
                messageAccumulator_.clear();
            }
            else
            {
                messageAccumulator_ += incomingByte;
            }
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
        Command newCMD{};

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
            newCMD.command = Commands::UNKNOWN;
        }

        for (std::size_t i = 0; i < CommandCount; ++i)
        {
            if (0 == std::strcmp(tokens[0], commandTable[i].str))
            {
                newCMD.command = commandTable[i].cmd;
                break;
            }
        }

        for (std::size_t j = 1; j < token_count && newCMD.argCount < 2; j++)
        {
            std::strncpy(newCMD.args[newCMD.argCount], tokens[j], sizeof(newCMD.args[0]) - 1);
            newCMD.args[newCMD.argCount][sizeof(newCMD.args[0]) - 1] = '\0';
            newCMD.argCount++;
        }
        
        return newCMD;
    }
// -----------------------------------------------------------------------------
    void runCommand(Command cmd) noexcept override
    {}

    Logic()                             = delete;
    Logic(const Logic&)                 = delete;
    Logic(Logic&&)                      = delete;
    Logic& operator=(const Logic&)      = delete;
    Logic& operator=(Logic&&)           = delete;

private:

    /** ADCs **/
    std::array<std::unique_ptr<driver::adc::Interface>,
        static_cast<std::size_t>(driver::adc::Id::COUNT)> adcs_;

    /** GPIO pins **/
    std::array<std::unique_ptr<driver::gpio::Interface>,
        static_cast<std::size_t>(driver::gpio::Id::COUNT)> gpios_;

    /** Timers **/
    std::array<std::unique_ptr<driver::timer::Interface>,
        static_cast<std::size_t>(driver::timer::Id::COUNT)> timers_;

    /** Serial device used to read/write messages and commands **/
    std::unique_ptr<driver::serial::Interface> serial_;

    /** Temperature sensor **/
    std::unique_ptr<driver::tempsensor::Interface> tempsensor_;

    std::string messageAccumulator_;
};

}
