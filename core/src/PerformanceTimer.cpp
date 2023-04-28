#include "PerformanceTimer.h"


namespace DesignPatterns
{
	PerformanceTimer::PerformanceTimer()
	{
		m_running = false;
		m_paused = false;
		m_startTime = std::chrono::high_resolution_clock::now();
		m_endTime = std::chrono::high_resolution_clock::now();
		m_nanosOut = nullptr;
		m_accumulateNanos = 0;
	}
	PerformanceTimer::PerformanceTimer(long long& nanosOut, bool autostart)
	{
		m_nanosOut = &nanosOut;
		m_running = false;
		m_paused = false;
		m_startTime = std::chrono::high_resolution_clock::now();
		m_endTime = std::chrono::high_resolution_clock::now();
		m_accumulateNanos = 0;
		if (autostart)
			start();
	}
	PerformanceTimer::~PerformanceTimer()
	{
		stop();
		if (m_nanosOut)
		{
			try {
				*m_nanosOut = elapsed_nanos();
			}
			catch (...) {}
		}		
	}

	void PerformanceTimer::start()
	{
		if (m_paused)
		{
			
			m_paused = false;
			m_startTime = std::chrono::high_resolution_clock::now();
			return;
		}
		if (m_running) return;
		m_running = true;
		m_paused = false;
		m_accumulateNanos = 0;
		m_startTime = std::chrono::high_resolution_clock::now();
	}
	bool PerformanceTimer ::isRunning() const
	{
		return m_running;
	}
	void PerformanceTimer::pause()
	{
		if (m_paused)
			return;
		m_endTime = std::chrono::high_resolution_clock::now();
		m_accumulateNanos += std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime).count();
		m_paused = true;
	}
	void PerformanceTimer::stop()
	{
		if (!m_running)
			return;
		if (!m_paused)
		{
			m_endTime = std::chrono::high_resolution_clock::now();
			m_accumulateNanos += std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime).count();
		}
		m_paused = false;
		m_running = false;
	}

	void PerformanceTimer::restart()
	{
		m_accumulateNanos = 0;
		m_running = true;
		m_paused = false;
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	long long PerformanceTimer::elapsed_nanos() const
	{
		if (m_paused)
		{
			return m_accumulateNanos;
		}
		if (m_running)
		{
			m_endTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
			return elapsed.count();
		}
		return m_accumulateNanos;
	}
	double PerformanceTimer::elapsed_micros() const
	{
		if (m_paused)
		{
			return m_accumulateNanos;
		}
		if (m_running)
		{
			m_endTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
			return elapsed.count() * 0.001;
		}
		return (double)m_accumulateNanos * 0.001;
	}
	double PerformanceTimer::elapsed_millis() const
	{
		if (m_paused)
		{
			return  (double)m_accumulateNanos * 0.000001;
		}
		if (m_running)
		{
			m_endTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(m_endTime - m_startTime);
			return elapsed.count() * 0.001;
		}
		return (double)m_accumulateNanos * 0.000001;
	}
	double PerformanceTimer::elapsed_seconds() const
	{
		if (m_paused)
		{
			return (double)m_accumulateNanos * 0.000000001;
		}
		if (m_running)
		{
			m_endTime = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_endTime - m_startTime);
			return elapsed.count() * 0.001;
		}
		return (double)m_accumulateNanos * 0.000000001;
	}
}