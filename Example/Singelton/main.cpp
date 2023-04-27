#include "../exampleHelper.h"

const Example::Info Example::info =
{
	"Singelton",
	"This is a example to show the usage of the singelton template"
};

// Create a new Singelton class
class Singelton_1 : public DesignPatterns::Singleton<Singelton_1> // Uses the classname as template param
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
class Singelton_2 : public DesignPatterns::Singleton<Singelton_2>
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

int main(int argc, char* argv[])
{
	Example::init();

	Singelton_1& instance = Singelton_1::getInstance();
	std::cout << "Singelton_1.getName(): " << instance.getName() << "\n";

	std::cout << "Singelton_2.getName(): " << Singelton_2::getName() << "\n";

	getchar();
	return 0;
}