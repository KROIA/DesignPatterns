#pragma once

#include "Test.h"

namespace UnitTest
{
	class TestRunner
	{
	public:
		TestRunner();
		~TestRunner();

		void addTest(Test* test);
		bool runTests();
		void printResults();
	private:
		std::vector<Test*> m_tests;
	};
}