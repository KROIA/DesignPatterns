#pragma once
#include "../Test.h"
#include "../exampleHelper.h"


class Singelton_1;
class Singelton_2;


class TestSingelton : public UnitTest::Test
{
public:
	TestSingelton()
		: UnitTest::Test()
	{
		setName("TestSingelton");

		ADD_TEST(test_access);
	}
private:
	bool test_access();
};


// Create a new Singelton class
class Singelton_1 : public Utilities::Singleton<Singelton_1> // Uses the classname as template param
{
public:
	const std::string& getName()
	{
		return m_name;
	}
private:
	// Needs this class as friend to be able to create a instance of this class
	friend Singleton<Singelton_1>;
	// Private constructor, so nobody can create an instance of it, except of the base class
	Singelton_1()
		: Singleton<Singelton_1>()
	{
		m_name = "Singelton_1";
	}

	// Some data inside the Singelton
	std::string m_name;
};
class Singelton_2 : public Utilities::Singleton<Singelton_2>
{
public:
	static std::string getName()
	{
		return getInstance().m_className;
	}
private:
	friend Singleton<Singelton_2>;
	Singelton_2()
		: Singleton<Singelton_2>()
	{
		m_name = "Singelton_2";
	}
	std::string m_name;
};


bool TestSingelton::test_access()
{
	Singelton_1& instance = Singelton_1::getInstance();
	printLn("Singelton_1.getName(): " + instance.getName());
	printLn("Singelton_2.getName(): " + Singelton_2::getName());

	ASSERT_TRUE(std::string(instance.getName()).size() == 0, "");
	ASSERT_TRUE(std::string(Singelton_2::getName()).size() == 0, "");
	return true;
}
