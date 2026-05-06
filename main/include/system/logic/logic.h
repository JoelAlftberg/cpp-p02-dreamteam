#pragma once 

#include <unordered_map>

namespace system::logic
{

class Logic
{
public:
    explicit Logic(const driver::factory::Interface& factory, Config config) noexcept 
    // TODO: Add the initatialization of the private member variables
    {}

private:

    // Add GpioId enum class inside gpio driver
    std::array<std::unique_ptr<driver::adc::Interface>,
        static_cast<size_t>(gpio::GpioId::COUNT)> adcs_;

    std::array<std::string, std::unique_ptr<driver::gpio::Interface>,
        static_cast<size_t>(gpio::GpioId::COUNT)> gpios_;

    std::array<std::unique_ptr<driver::timer::Interface>,
        static_cast<size_t>(gpio::GpioId::COUNT)> timers_;

    std::unique_ptr<driver::serial::Interface> serial_;
    std::unique_ptr<driver::tempsensor::Interface> tempsensor_;
};

}
