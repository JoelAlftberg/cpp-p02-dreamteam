/**
 * @brief Unit tests for the GPIO driver stub.
 */
#include "driver/gpio/stub.h"
#include "yrgo/test/test.h"

#ifdef TESTSUITE

namespace driver
{
namespace
{
/**
 * @brief Initialization test.
 *
 *        Verify that the stub is always initialized, and that it reports the mode given at
 *        construction.
 */
TEST(Gpio_Stub, Initialization)
{
    gpio::Stub input{gpio::Mode::Input};
    EXPECT_TRUE(input.isInitialized());
    EXPECT_EQ(static_cast<int>(input.mode()), static_cast<int>(gpio::Mode::Input));

    gpio::Stub output{gpio::Mode::Output};
    EXPECT_TRUE(output.isInitialized());
    EXPECT_EQ(static_cast<int>(output.mode()), static_cast<int>(gpio::Mode::Output));
}

/**
 * @brief Write and read test.
 *
 *        Verify that a value written to the stub can be read back.
 */
TEST(Gpio_Stub, WriteAndRead)
{
    gpio::Stub led{gpio::Mode::Output};
    EXPECT_FALSE(led.read());

    led.write(true);
    EXPECT_TRUE(led.read());

    led.write(false);
    EXPECT_FALSE(led.read());
}

/**
 * @brief Toggle test.
 *
 *        Verify that toggle() inverts the current output.
 */
TEST(Gpio_Stub, Toggle)
{
    gpio::Stub led{gpio::Mode::Output};
    EXPECT_FALSE(led.read());

    led.toggle();
    EXPECT_TRUE(led.read());

    led.toggle();
    EXPECT_FALSE(led.read());
}

/**
 * @brief Simulated input test.
 *
 *        Verify that setState() can be used to simulate an external input, e.g. a button press,
 *        without going through write().
 */
TEST(Gpio_Stub, SimulatedInput)
{
    gpio::Stub button{gpio::Mode::InputPullup};
    EXPECT_FALSE(button.read());

    button.setState(true);
    EXPECT_TRUE(button.read());

    button.setState(false);
    EXPECT_FALSE(button.read());
}

/**
 * @brief Interrupt test.
 *
 *        Verify that pin change interrupt enablement is tracked, both for the GPIO itself and
 *        for its associated I/O port.
 */
TEST(Gpio_Stub, Interrupt)
{
    gpio::Stub button{gpio::Mode::InputPullup};
    EXPECT_FALSE(button.isInterruptEnabled());
    EXPECT_FALSE(button.isPortInterruptEnabled());

    button.enableInterrupt(true);
    EXPECT_TRUE(button.isInterruptEnabled());

    button.enableInterrupt(false);
    EXPECT_FALSE(button.isInterruptEnabled());

    button.enableInterruptOnPort(true);
    EXPECT_TRUE(button.isPortInterruptEnabled());
}
} // namespace
} // namespace driver

#endif /** TESTSUITE */
