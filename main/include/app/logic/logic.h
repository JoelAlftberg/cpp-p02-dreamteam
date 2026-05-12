#pragma once 

#include "driver/common/utils.h"

#include "driver/adc/types.h"
#include "driver/gpio/types.h"
#include "driver/timer/types.h"

#include "app/logic/interface.h"
#include "driver/config/interface.h"
#include "driver/factory/interface.h"
#include "driver/gpio/interface.h"
#include "driver/timer/interface.h"


#include <array>
#include <cstddef>
#include <iostream>
#include <memory>

using driver::utils::to_idx;

namespace app::logic
{

class Logic final : public Interface
{
public:
    explicit Logic(
            const driver::factory::Interface& factory,
            driver::config::Interface& config
            ) noexcept 
    {
        const auto& ledSettings = config.getGpio(driver::gpio::Id::LedYellow);
        if (ledSettings.isEnabled)
        {
            const auto index = to_idx(driver::gpio::Id::LedYellow);
            gpios_[index] = factory.gpio(ledSettings);
        }

        const auto& timerSettings = config.getTimer(driver::timer::Id::Blink);
        if (timerSettings.isEnabled) {
            const auto index = to_idx(driver::timer::Id::Blink);
            timers_[index] = factory.timer(timerSettings);
        }

    }

    void run() noexcept override
    { 
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 
        auto& led = gpios_[to_idx(driver::gpio::Id::LedYellow)];
        blinkTimer->tick();

        if(blinkTimer->hasTimedOut())
        {
            led->toggle();
        }
    }

    void initialize() noexcept 
    {
        auto& blinkTimer = timers_[to_idx(driver::timer::Id::Blink)]; 
        if (blinkTimer)
        {
            blinkTimer->start();
        }

        auto& led = gpios_[to_idx(driver::gpio::Id::LedYellow)];
        if (led)
        {
            led->on();
        }
    }
    
    bool isInitialized() const noexcept override
    {
        return true;
    }

    Command parseCommand(const char* input) noexcept override
    {
        return Command{};
    }

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
};

}
