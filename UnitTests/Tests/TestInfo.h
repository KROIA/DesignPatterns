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
	printLn(std::string("Version:    ") + Utilities::Info::version);
	printLn(std::string("Autor:      ") + Utilities::Info::autor);
	printLn(std::string("Date:       ") + Utilities::Info::date);
	printLn(std::string("Build Type: ") + Utilities::Info::buildType);

	ASSERT_TRUE(std::string(Utilities::Info::version).size() == 0, "")
	ASSERT_TRUE(std::string(Utilities::Info::autor).size() == 0, "")
	ASSERT_TRUE(std::string(Utilities::Info::date).size() == 0, "")
	ASSERT_TRUE(std::string(Utilities::Info::buildType).size() == 0, "")

	return true;
}