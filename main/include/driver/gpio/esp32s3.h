//** GPIO-driver for the esp32s3. */
#pragma once

#include "driver/gpio/interface.h"


namespace driver::gpio
{


    class Esp32s3 final : public Interface
    {
        public:
            //Constructor
            explicit init(std::uint32_t pin) noexcept;

            void on(std::uint32_t pin) noexcept override;

            void off(std::uint32_t pin) noexcept override;

            bool read(std::uint32_t pin) noexcept override;

            void toggle(std::uint32_t pin, const std::uint32_t timeout_ms) noexcept override;

        private:




    }

}// namespace driver::gpio
