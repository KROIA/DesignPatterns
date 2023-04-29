#pragma once

#include "DesignPatterns_global.h"
#include <chrono>

// MSVC Compiler
#ifdef _MSC_VER 
#define __PRETTY_FUNCTION__ __FUNCSIG__
typedef std::chrono::steady_clock::time_point TimePoint;
#else
typedef std::chrono::system_clock::time_point TimePoint;
#endif

namespace DesignPatterns
{
    /**
     *  @brief A class for measuring performance time.
     */
    class DESIGN_PATTERNS_EXPORT PerformanceTimer
    {
        public:
        /*
         * @brief Constructs a PerformanceTimer object.
         */
        PerformanceTimer();

        /**
         *  @brief Constructs a PerformanceTimer object with an output parameter to store the elapsed time.
         *  @param nanosOut A reference to a long long variable to store the elapsed time in nanoseconds.
         *                  the value is updated on calls: pause(), stop(), restart(), ~PerformanceTimer()
         *  @param autostart Whether to automatically start the timer upon construction.
         */
        PerformanceTimer(long long& nanosOut, bool autostart = true);

        /**
         *  @brief Destroys the PerformanceTimer object.
         */
        ~PerformanceTimer();

        /**
         *  @brief Starts the timer.
         */
        void start();

        /**
         *  @brief Checks if the timer is running.
         *  @return True if the timer is running, false otherwise.
         */
        bool isRunning() const;

        /**
         *  @brief Pauses the timer.
         */
        void pause();

        /**
         *  @brief Stops the timer.
         */
        void stop();

        /**
         *  @brief Restarts the timer.
         */
        void restart();

        /**
         *  @brief Returns the elapsed time in nanoseconds.
         *  @return The elapsed time in nanoseconds.
         */
        long long elapsed_nanos() const;

        /**
         *  @brief Returns the elapsed time in microseconds.
         *  @return The elapsed time in microseconds.
         */
        double elapsed_micros() const;

        /**
         *  @brief Returns the elapsed time in milliseconds.
         *  @return The elapsed time in milliseconds.
         */
        double elapsed_millis() const;

        /**
         *  @brief Returns the elapsed time in seconds.
         *  @return The elapsed time in seconds.
         */
        double elapsed_seconds() const;

    private:
        TimePoint m_startTime;
        mutable TimePoint m_endTime;
        bool m_running;
        bool m_paused;
        long long* m_nanosOut;
        long long m_accumulateNanos;
    };
}