#pragma once 

#include "driver/config/interface.h"
#include "driver/factory/interface.h"
#include "system/logic/interface.h"

#include <memory>
#include <array>

namespace system::logic
{

class Logic final : public Interface
{
public:
    explicit Logic(
            const driver::factory::Interface& factory,
            driver::config::Interface& config
            ) noexcept 
    {}

    Logic()                             = delete;
    Logic(const Logic&)                 = delete;
    Logic(Logic&&)                      = delete;
    Logic& operator=(const Logic&)      = delete;
    Logic& operator=(Logic&&)           = delete;

private:

    /** ADCs **/
    std::array<std::unique_ptr<driver::adc::Interface>,
        static_cast<size_t>(5U)> adcs_;

    /** GPIO pins **/
    std::array<std::string, std::unique_ptr<driver::gpio::Interface>,
        static_cast<size_t>(5U)> gpios_;

    /** Timers **/
    std::array<std::unique_ptr<driver::timer::Interface>,
        static_cast<size_t>(5U)> timers_;

    /** Serial device used to read/write messages and commands **/
    std::unique_ptr<driver::serial::Interface> serial_;

    /** Temperature sensor **/
    std::unique_ptr<driver::tempsensor::Interface> tempsensor_;
};

}
