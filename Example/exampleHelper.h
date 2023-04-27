#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <iostream>

#include "DesignPatterns.h"

namespace Example
{
	struct Info
	{
		std::string name;
		std::string description;
	};
	extern const Info info;

	void init()
	{
		std::cout << "Project:     " << info.name << "\n";
		std::cout << "Description: " << info.description << "\n";

		std::cout << "+----------------------------------------------------\n";
		std::cout << "| Library info:\n";
		std::cout << "|   Version:    " << DesignPatterns::Info::version << "\n";
		std::cout << "|   Autor:      " << DesignPatterns::Info::autor << "\n";
		std::cout << "|   Date:       " << DesignPatterns::Info::date << "\n";
		std::cout << "|   Build Type: " << DesignPatterns::Info::buildType << "\n";
		std::cout << "+----------------------------------------------------\n";
	}
}

namespace UnitTest
{
	namespace Result
	{
		int testCount;
		int passes;
		int fails;
	};
	namespace Color
	{
		const std::string red = "\033[31m";
		const std::string green = "\033[32m";
		const std::string yellow = "\033[33m";
		const std::string white = "\033[0m";
	};

#define FILESOURCE std::string(std::string(__FILE__)+"\nLine: "+std::to_string(__LINE__)+"  ")

	// Asserts the test with a message
#define ASSERT(msg) \
	UnitTest::printLn(msg, UnitTest::Color::red); \
	return false; 

	// Asserts if a is equal to b
#define ASSERT_EQUAL(a, b, msg) \
	if((a) == (b)) \
	{ \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string(#a " must be equal to "#b), UnitTest::Color::red); \
		if(std::string(msg).length() > 0) \
			UnitTest::printLn("    "+std::string(msg), UnitTest::Color::yellow); \
		return false; \
	}

	// Asserts if a is not equal to b
#define ASSERT_NEQUAL(a, b, msg) \
	if((a) != (b)) \
	{ \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string(#a " must not be equal to "#b), UnitTest::Color::red); \
		if(std::string(msg).length() > 0) \
			UnitTest::printLn("    "+std::string(msg), UnitTest::Color::yellow); \
		return false; \
	}

	// Asserts if <check> is true
#define ASSERT_TRUE(check, msg) \
	if(check) \
	{ \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string(#check " shuld not be true\n"), UnitTest::Color::red); \
		if(std::string(msg).length() > 0) \
			UnitTest::printLn("    "+std::string(msg), UnitTest::Color::yellow); \
		return false; \
	} 

		// Asserts if <check> is false
#define ASSERT_FALSE(check, msg) \
	if(!check) \
	{ \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string(#check " shuld not be false\n"), UnitTest::Color::red); \
		if(std::string(msg).length() > 0) \
			UnitTest::printLn("    "+std::string(msg), UnitTest::Color::yellow); \
		return false; \
	} 

	// Runns a test function
#define TEST_RUN(func, ...) \
	try { \
		UnitTest::Result::testCount++; \
		if(func( __VA_ARGS__ )) \
		{ \
			UnitTest::Result::passes++; \
			UnitTest::print(">>    Test "+std::string(#func"("#__VA_ARGS__")")); \
			UnitTest::printLn("   [PASS]", UnitTest::Color::green); \
		}else{ \
			UnitTest::Result::fails++; \
			UnitTest::print(">>    Test "+std::string(#func"("#__VA_ARGS__")")); \
			UnitTest::printLn("   [FAIL]", UnitTest::Color::red); \
		} \
	} catch(const std::runtime_error &e){ \
		UnitTest::Result::fails++; \
		UnitTest::print(">>    Test " + std::string(#func"("#__VA_ARGS__")")); \
		UnitTest::printLn("   [FAIL]", UnitTest::Color::red); \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string("   Exception: ")+e.what(), UnitTest::Color::red); \
	} catch(...) { \
		UnitTest::Result::fails++; \
		UnitTest::print(">>    Test " + std::string(#func"("#__VA_ARGS__")")); \
		UnitTest::printLn("   [FAIL]", UnitTest::Color::red); \
		UnitTest::printLn(FILESOURCE, UnitTest::Color::yellow); \
		UnitTest::printLn("    "+std::string("   Exception: unknown"), UnitTest::Color::red); \
	}

	void printLn(std::string msg, const std::string& color = Color::white);
	void print(std::string msg, const std::string& color = Color::white);

	void reset()
	{
		Result::fails = 0;
		Result::testCount = 0;
		Result::passes = 0;
		printLn("Reset Testresults");
	}
	void printResults()
	{
		printLn("---------------------------------------------", Color::yellow);
		printLn("Tests run:    " + std::to_string(Result::testCount), Color::yellow);
		printLn("Tests failed: " + std::to_string(Result::fails), (Result::fails==0?Color::green:Color::red));
		printLn("Tests passed: " + std::to_string(Result::passes), (Result::passes==Result::testCount?Color::green:(Result::passes==0?Color::red:Color::yellow)));
		printLn("---------------------------------------------", Color::yellow);
	}

	void print(std::string msg, const std::string& color)
	{
		size_t newLinePos = msg.find_last_of("\n");
		bool useNewLine = false;
		if (newLinePos == msg.size()-1)
		{
			msg = msg.substr(0, newLinePos);
			useNewLine = true;
		}
		std::cout << color << msg << Color::white;
		if(useNewLine)
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
		std::cout << color << msg << Color::white;
		if (useNewLine)
			std::cout << "\n";
	}
}