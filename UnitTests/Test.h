#pragma once

#include <iostream>
#include <vector>
#include <functional>
namespace Color
{
	extern const std::string red;
	extern const std::string green;
	extern const std::string yellow;
	extern const std::string white;
};
namespace UnitTest
{
	

	class Test {
	public:
		Test();

		bool start();
		void printResults();
		void reset();
		size_t testCount();
		size_t passCount();
		const std::string& getName();

		void contextDepthAdd();
		void contextDepthSubtract();

	protected:
		void setName(const std::string& testName);
		void addTest(std::function<bool()> testFunc, const std::string& name);

		void print(const std::string& msg, const std::string& color = Color::white);
		void printLn(const std::string& msg, const std::string& color = Color::white);
		void printError(const std::string& msg);
		void printLnError(const std::string& msg);
		void printError(const std::string& msg, const std::string& color);
		void printLnError(const std::string& msg, const std::string& color);


	private:


		void internal_print(std::string msg, const std::string& color);
		void internal_printLn(std::string msg, const std::string& color);

		std::string m_testName;

		struct Message
		{
			std::string msg;
			std::string color;
		};
		struct TestData
		{
			std::function<bool()> func;
			std::vector<Message> msgs;
			std::vector<Message> errors;
			bool passed;
			std::string name;
		};

		std::vector<TestData> m_testFuncs;
		TestData* m_currentTestData;
		bool m_testsRunning;
		int m_contextDepth;
	};


}
namespace Console
{
	extern void print(std::string msg, const std::string& color);
	extern void printLn(std::string msg, const std::string& color);
}


#define ADD_TEST(testFunc) \
	addTest([&]() { return testFunc(); }, #testFunc);

#define FILESOURCE std::string(std::string(__FILE__)+"\nLine: "+std::to_string(__LINE__)+"  ")

// Asserts the test with a message
#define ASSERT(msg) \
	printLnError(msg, Color::red); \
	return false; 

	// Asserts if a is equal to b
#define ASSERT_EQUAL(a, b, msg) \
	if((a) == (b)) \
	{ \
		printLnError(FILESOURCE, Color::yellow); \
		printLnError("    "+std::string(#a " must be equal to "#b), Color::red); \
		if(std::string(msg).length() > 0) \
			printLnError("    "+std::string(msg), Color::yellow); \
		return false; \
	}

	// Asserts if a is not equal to b
#define ASSERT_NEQUAL(a, b, msg) \
	if((a) != (b)) \
	{ \
		printLnError(FILESOURCE, Color::yellow); \
		printLnError("    "+std::string(#a " must not be equal to "#b), Color::red); \
		if(std::string(msg).length() > 0) \
			printLnError("    "+std::string(msg), Color::yellow); \
		return false; \
	}

	// Asserts if <check> is true
#define ASSERT_TRUE(check, msg) \
	if(check) \
	{ \
		printLnError(FILESOURCE, Color::yellow); \
		printLnError("    "+std::string(#check " shuld not be true\n"), Color::red); \
		if(std::string(msg).length() > 0) \
			printLnError("    "+std::string(msg), Color::yellow); \
		return false; \
	} 

		// Asserts if <check> is false
#define ASSERT_FALSE(check, msg) \
	if(!check) \
	{ \
		printLnError(FILESOURCE, Color::yellow); \
		printLnError("    "+std::string(#check " shuld not be false\n"), Color::red); \
		if(std::string(msg).length() > 0) \
			printLnError("    "+std::string(msg), Color::yellow); \
		return false; \
	} 