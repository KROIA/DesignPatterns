#pragma once
#include "../Test.h"
#include "../exampleHelper.h"

class TestInfo : public UnitTest::Test
{
public:
	TestInfo()
		: UnitTest::Test()
	{
		setName("TestInfo");

		ADD_TEST(test_printInfo);
	}
private:
	bool test_printInfo();
};

bool TestInfo::test_printInfo()
{
	printLn(std::string("Version:    ") + DesignPatterns::Info::version);
	printLn(std::string("Autor:      ") + DesignPatterns::Info::autor);
	printLn(std::string("Date:       ") + DesignPatterns::Info::date);
	printLn(std::string("Build Type: ") + DesignPatterns::Info::buildType);

	ASSERT_TRUE(std::string(DesignPatterns::Info::version).size() == 0)
	ASSERT_TRUE(std::string(DesignPatterns::Info::autor).size() == 0)
	ASSERT_TRUE(std::string(DesignPatterns::Info::date).size() == 0)
	ASSERT_TRUE(std::string(DesignPatterns::Info::buildType).size() == 0)

	return true;
}