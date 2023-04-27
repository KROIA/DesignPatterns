#pragma once
#include "DesignPatterns.h"

class Object1 : public DesignPatterns::Object
{
public:
	Object1(DesignPatterns::ObjectManager &manager, int val)
		: Object(manager)
		, value(val)
	{

	}
	int getValue()
	{
		return value;
	}
private:

	int value;
};