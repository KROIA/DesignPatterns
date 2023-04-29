#include "TestRunner.h"
#include <string>

namespace UnitTest
{
	TestRunner::TestRunner()
	{

	}
	TestRunner::~TestRunner()
	{
		for (size_t i = 0; i < m_tests.size(); ++i)
			delete m_tests[i];
		m_tests.clear();
	}

	void TestRunner::addTest(Test* test)
	{
		if(test)
			m_tests.push_back(test);
	}
	bool TestRunner::runTests()
	{
		bool pass = true;
		for (size_t i = 0; i < m_tests.size(); ++i)
		{
			m_tests[i]->contextDepthAdd();
			pass &= m_tests[i]->start();
			m_tests[i]->contextDepthSubtract();
		}
		Console::printLn("---------------------------------------------", Color::white);
		Console::printLn("----------TestRunner  finished---------------", Color::white);
		Console::printLn("---------------------------------------------", Color::white);
		return pass;
	}
	void TestRunner::printResults()
	{
		int passes = 0;
		int fails = 0;
		int tests = 0;
		
		for (size_t i = 0; i < m_tests.size(); ++i)
		{
			m_tests[i]->printResults();
			passes += m_tests[i]->passCount();
			tests += m_tests[i]->testCount();
		}
		fails = tests - passes;
		Console::printLn("---------------------------------------------", Color::yellow);
		Console::printLn("Tests run:    " + std::to_string(tests), Color::yellow);
		Console::printLn("Tests failed: " + std::to_string(fails), (fails == 0 ? Color::green : Color::red));
		Console::printLn("Tests passed: " + std::to_string(passes), (passes == tests ? Color::green : (passes == 0 ? Color::red : Color::yellow)));
		Console::printLn("---------------------------------------------", Color::yellow);
	}
}