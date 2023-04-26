#include "DesignPatterns.h"
#include <iostream>


int main(int argc, char* argv[])
{
	std::cout << "Version:    " << DesignPatterns::Info::version		<< "\n";
	std::cout << "Autor:      " << DesignPatterns::Info::autor			<< "\n";
	std::cout << "Date:       " << DesignPatterns::Info::date			<< "\n";
	std::cout << "Build Type: " << DesignPatterns::Info::buildType		<< "\n";
	getchar();
	return 0;
}