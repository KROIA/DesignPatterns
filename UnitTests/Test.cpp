#include "Test.h"
#include <string>

namespace Color
{
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	const std::string yellow = "\033[33m";
	const std::string white = "\033[0m";
};
namespace UnitTest
{
	

	Test::Test()
	{
		m_currentTestData = nullptr;
		m_testsRunning = false;
		m_contextDepth = 0;
		m_testFuncs.reserve(50);
	}



	bool Test::start()
	{
		bool allPassed = true;
		reset();
		m_testsRunning = true;
		internal_printLn("Start Test: " + m_testName, Color::yellow);
		m_contextDepth++;
		for (auto& test : m_testFuncs) {
			m_currentTestData = &test;
			bool passed = false;

			internal_printLn("Start Testfunction: " + test.name, Color::yellow);
			m_contextDepth++;
			try
			{
				test.passed = false;
				passed = test.func();
				test.passed = passed;
			}
			catch (const std::runtime_error& e)
			{
				printLnError(e.what());
			}
			catch (const std::exception& e)
			{
				printLnError(e.what());
			}
			catch (...)
			{
				printLnError("unknown error");
			}
			m_contextDepth--;
			internal_print("Test: " + test.name, Color::yellow);
			if (passed)
			{
				internal_printLn("    [PASS]", Color::green);
			}
			else
			{
				internal_printLn("    [FAIL]", Color::red);
			}

			allPassed &= passed;
		}
		m_contextDepth--;

		m_currentTestData = nullptr;
		m_testsRunning = false;
		return allPassed;
	}
	void Test::printResults()
	{
		internal_printLn("Results for: " + m_testName, Color::yellow);
		m_contextDepth++;
		int passes = 0;
		int fails = 0;
		for (size_t i = 0; i < m_testFuncs.size(); ++i)
		{
			if (m_testFuncs[i].passed)
				passes++;
			else
				fails++;
			internal_print("Results for Test: " + m_testFuncs[i].name, Color::yellow);
			if(m_testFuncs[i].passed)
				internal_printLn("    [PASS]", Color::green);
			else
				internal_printLn("    [FAIL]", Color::red);

			m_contextDepth++;
			for (size_t j = 0; j < m_testFuncs[i].msgs.size(); ++j)
			{
				internal_printLn(m_testFuncs[i].msgs[j].msg, m_testFuncs[i].msgs[j].color);
			}
			for (size_t j = 0; j < m_testFuncs[i].errors.size(); ++j)
			{
				internal_printLn(m_testFuncs[i].errors[j].msg, m_testFuncs[i].errors[j].color);
			}
			m_contextDepth--;
		}
		internal_printLn("---------------------------------------------", Color::yellow);
		internal_printLn("Tests run:    " + std::to_string(m_testFuncs.size()), Color::yellow);
		internal_printLn("Tests failed: " + std::to_string(fails), (fails == 0 ? Color::green : Color::red));
		internal_printLn("Tests passed: " + std::to_string(passes), (passes == m_testFuncs.size() ? Color::green : (passes == 0 ? Color::red : Color::yellow)));
		internal_printLn("---------------------------------------------", Color::yellow);
		m_contextDepth--;
	}
	void Test::reset()
	{
		for (size_t i = 0; i < m_testFuncs.size(); ++i)
		{
			m_testFuncs[i].errors.clear();
			m_testFuncs[i].msgs.clear();
			m_testFuncs[i].passed = false;
		}
	}
	size_t Test::testCount()
	{
		return m_testFuncs.size();
	}
	size_t Test::passCount()
	{
		size_t passes = 0;
		for (size_t i = 0; i < m_testFuncs.size(); ++i)
		{
			if (m_testFuncs[i].passed)
				passes++;
		}
		return passes;
	}
	const std::string& Test::getName()
	{
		return m_testName;
	}
	void Test::contextDepthAdd()
	{
		m_contextDepth++;
	}
	void Test::contextDepthSubtract()
	{
		m_contextDepth--;
	}

	void Test::setName(const std::string& testName)
	{
		m_testName = testName;
	}
	void Test::addTest(std::function<bool()> testFunc, const std::string& name)
	{
		TestData data;
		data.func = testFunc;
		data.passed = false;
		data.name = name;

		m_testFuncs.push_back(data);
	}

	void Test::print(const std::string& msg, const std::string& color)
	{
		internal_print(msg, color);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = color;
			message.msg = msg;
			m_currentTestData->msgs.push_back(message);
		}
	}
	void Test::printLn(const std::string& msg, const std::string& color)
	{
		internal_printLn(msg, color);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = color;
			message.msg = msg + "\n";
			m_currentTestData->msgs.push_back(message);
		}
	}
	void Test::printError(const std::string& msg)
	{
		Console::print(msg, Color::red);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = Color::red;
			message.msg = msg + "\n";
			m_currentTestData->errors.push_back(message);
		}
	}
	void Test::printLnError(const std::string& msg)
	{
		Console::printLn(msg, Color::red);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = Color::red;
			message.msg = msg + "\n";
			m_currentTestData->errors.push_back(message);
		}
	}
	void Test::printError(const std::string& msg, const std::string& color)
	{
		Console::print(msg, Color::red);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = color;
			message.msg = msg + "\n";
			m_currentTestData->errors.push_back(message);
		}
	}
	void Test::printLnError(const std::string& msg, const std::string& color)
	{
		Console::printLn(msg, Color::red);
		if (m_currentTestData && m_testsRunning)
		{
			Message message;
			message.color = color;
			message.msg = msg + "\n";
			m_currentTestData->errors.push_back(message);
		}
	}

	void Test::internal_print(std::string msg, const std::string& color)
	{
		Console::print(std::string(m_contextDepth * 4, ' ') + msg, color);
	}
	void Test::internal_printLn(std::string msg, const std::string& color)
	{
		Console::printLn(std::string(m_contextDepth * 4, ' ') + msg, color);
	}
}
namespace Console
{
	void print(std::string msg, const std::string& color)
	{
		size_t newLinePos = msg.find_last_of("\n");
		bool useNewLine = false;
		if (newLinePos == msg.size() - 1)
		{
			msg = msg.substr(0, newLinePos);
			useNewLine = true;
		}
		//std::cout << std::string(' ', m_contextDepth * 4);
		std::cout << color << msg << Color::white;
		if (useNewLine)
			std::cout << "\n";

	}
	void printLn(std::string msg, const std::string& color)
	{
		size_t newLinePos = msg.find_last_of("\n");
		bool useNewLine = true;
		if (newLinePos == msg.size() - 1)
		{
			msg = msg.substr(0, newLinePos);
		}
		//std::cout << std::string(' ', m_contextDepth * 4);
		std::cout << color << msg << Color::white;
		if (useNewLine)
			std::cout << "\n";
	}
}