#pragma once
#include "DesignPatterns.h"

class Object1 : public DesignPatterns::Object
{
public:
	Object1(size_t id, int val)
		: Object(id)
		, value(val)
	{

	}
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