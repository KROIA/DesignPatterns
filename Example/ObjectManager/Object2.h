#pragma once
#include "DesignPatterns.h"
#include <string>

class Object2 : public DesignPatterns::Object
{
public:
	Object2(DesignPatterns::ObjectManager& manager, const std::string &text)
		: Object(manager)
		, text(text)
	{

	}
	const std::string& getText()
	{
		return text;
	}
private:

	std::string text;
};