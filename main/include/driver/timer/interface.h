#include <chrono>
#pragma once


namespace driver::timer
{
class Interface
{
public:
    /**
     * @brief Destructor
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Start the timer.
     */
    virtual void start() noexcept = 0;

    /**
     * @brief Stop the timer.
     */
    virtual void stop() noexcept = 0;

    /**
     * @brief Cheack if the timer is running.
     * 
     * @return True if the timer is running, false otherwise.
     */
    virtual bool isRunning() const noexcept = 0;

    /**
     * @brief Check if the timer has tiemd out.
     * 
     * @return True if the timer has timed out, false otherwise.
     */
    virtual bool hasTimedOut() noexcept = 0;

    /**
     * @brief Toggle the timer.
     */
    virtual void toggle() noexcept = 0;

    /**
     * @brief Increment the timer.
     * 
     * @note This operation is only performed if the timer is running.
     */
    virtual void tick() noexcept = 0;
    


};
} // Namespace timer