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
	class DESIGN_PATTERNS_EXPORT PerformanceTimer
	{
	public:
		PerformanceTimer();
		PerformanceTimer(long long& nanosOut, bool autostart = true);
		~PerformanceTimer();

		void start();
		bool isRunning() const;
		void pause();
		void stop();

		void restart();

		long long elapsed_nanos() const;
		double elapsed_micros() const;
		double elapsed_millis() const;
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