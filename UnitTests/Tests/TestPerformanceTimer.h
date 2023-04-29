#pragma once
#include "../Test.h"
#include "../exampleHelper.h"
#include <thread>
#include <random>
#include <math.h>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
long long preciseSleep(long long millis)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	Sleep(millis);
	auto t2 = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

class TestPerformanceTimer: public UnitTest::Test
{
public:
	TestPerformanceTimer()
	{
		setName("TestPerformanceTimer");

		ADD_TEST(test_startStop);
		ADD_TEST(test_elapsed);
		ADD_TEST(test_paused);
		ADD_TEST(test_restart);
		ADD_TEST(test_scope);
	}
private:
	bool test_startStop();
	bool test_elapsed();
	bool test_paused();
	bool test_restart();
	bool test_scope();
};



bool TestPerformanceTimer::test_startStop()
{
	DesignPatterns::PerformanceTimer timer;

	size_t testCount = 10;
	size_t millisMin = 5;
	size_t millisMax = 50;
	size_t microDiffTolerance = 10;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(millisMin, millisMax);
	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);
		timer.start();
		double compareTo = preciseSleep(millis);
		timer.stop();
		Sleep(millis);
		double elapsedMillis = timer.elapsed_millis();
		double dif = abs(elapsedMillis - compareTo);
		if (dif > microDiffTolerance)
		{
			ASSERT("Timer is out of tolerance. Timer = " + std::to_string(timer.elapsed_millis()) + "ms. Delayed for: " + std::to_string(compareTo) + "ms");
		}
	}
	return true;
}
bool TestPerformanceTimer::test_elapsed()
{
	DesignPatterns::PerformanceTimer timer;

	size_t repetitions = 5;
	size_t testCount = 10;
	size_t millisMin = 5;
	size_t millisMax = 50;
	size_t microDiffTolerance = 10;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(millisMin, millisMax);
	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);
		double compareTo = 0;
		for (long long j = 0; j < repetitions; ++j)
		{
			timer.start();

			compareTo += preciseSleep(millis);
			double elapsed = timer.elapsed_millis();
			if (abs(elapsed - compareTo) > microDiffTolerance)
			{
				ASSERT("Timer is out of tolerance. Timer = " + std::to_string(elapsed) + "ms. Delayed for: " + std::to_string(compareTo) + "ms");
			}
		}
		timer.stop();
	}
	return true;
}
bool TestPerformanceTimer::test_paused()
{
	DesignPatterns::PerformanceTimer timer;

	long long repetitions = 5;
	size_t testCount = 10;
	size_t millisMin = 5;
	size_t millisMax = 50;
	size_t microDiffTolerance = 10;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(millisMin, millisMax);
	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);
		double compareTo = 0;
		for (long long j = 0; j < repetitions; ++j)
		{
			timer.start();
			compareTo += preciseSleep(millis);
			timer.pause();
			Sleep(millis);
		}
		timer.stop();
		double elapsed = timer.elapsed_millis();
		if (abs(elapsed - compareTo) > microDiffTolerance)
		{
			ASSERT("Timer is out of tolerance. Timer = " + std::to_string(elapsed) + "ms. Delayed for: " + std::to_string(compareTo) + "ms");
		}
	}
	return true;
}
bool TestPerformanceTimer::test_restart()
{
	DesignPatterns::PerformanceTimer timer;

	size_t testCount = 10;
	size_t millisMin = 5;
	size_t millisMax = 50;
	size_t microDiffTolerance = 10;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(millisMin, millisMax);
	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);
		timer.start();
		Sleep(millis);
		timer.restart();
		double compareTo = preciseSleep(millis);
		timer.stop();
		Sleep(millis);
		double elapsed = timer.elapsed_millis();
		if (abs(elapsed - compareTo) > microDiffTolerance)
		{
			ASSERT("Timer is out of tolerance. Timer = " + std::to_string(elapsed) + "ms. Delayed for: " + std::to_string(compareTo) + "ms");
		}
	}
	return true;
}
bool TestPerformanceTimer::test_scope()
{
	size_t testCount = 30;
	size_t millisMin = 5;
	size_t millisMax = 50;
	size_t microDiffTolerance = 10;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(millisMin, millisMax);
	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);
		long long listener = 0;
		double compareTo = 0;
		{
			DesignPatterns::PerformanceTimer timer(listener);
			timer.start();
			compareTo = preciseSleep(millis);
		}
		Sleep(millis);
		double elapsed = listener / 1000000.0;
		if (abs(elapsed - compareTo) > microDiffTolerance)
		{
			ASSERT("Timer is out of tolerance. Timer = " + std::to_string(elapsed) + "us. Delayed for: " + std::to_string(compareTo) + "ms");
		}
	}

	for (size_t i = 0; i < testCount; ++i)
	{
		long long millis = distrib(gen);

		double compareTo = 0;
		try {
			DesignPatterns::PerformanceTimer* timer = nullptr;
			{
				long long listener = 0;
				timer = new DesignPatterns::PerformanceTimer(listener);
				timer->start();
				compareTo = preciseSleep(millis);
			}
			Sleep(millis);
			delete timer;
			timer = nullptr;
		}
		catch (std::runtime_error& e) {
			ASSERT(e.what());
		}
		catch (...)
		{
			ASSERT("An unknown error occured");
		}

	}
	return true;
}