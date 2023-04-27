
#include "../exampleHelper.h"

const Example::Info Example::info = 
{
	"Info",
	"This is a example to read the library info values"
};

int main(int argc, char* argv[])
{
	Example::init();

	std::cout << "Version:    " << DesignPatterns::Info::version		<< "\n";
	std::cout << "Autor:      " << DesignPatterns::Info::autor			<< "\n";
	std::cout << "Date:       " << DesignPatterns::Info::date			<< "\n";
	std::cout << "Build Type: " << DesignPatterns::Info::buildType		<< "\n";
	getchar();
	return 0;
}