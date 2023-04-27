#include "../exampleHelper.h"
#include "Object1.h"
#include "Object2.h"

const Example::Info Example::info =
{
	"ObjectManager",
	"This is a example to show the usage of the ObjectManager"
};

using std::cout;

bool test_fillManager();
bool test_getObjects();
bool test_removeObject();
bool test_doubleInsert();

int main(int argc, char* argv[])
{
	Example::init();
	UnitTest::reset();

	DesignPatterns::ObjectManager manager;
	
	TEST_RUN(test_fillManager);
	TEST_RUN(test_getObjects);
	TEST_RUN(test_removeObject);
	TEST_RUN(test_doubleInsert);


	UnitTest::printResults();
	getchar();

	Object1 *o1_1 = new Object1(manager, 1);
	Object1 *o1_2 = new Object1(manager, 2);
	Object1 *o1_3 = new Object1(manager, 3);

	Object2 *o2_1 = new Object2(manager, "O1");
	Object2 *o2_2 = new Object2(manager, "O2");
	Object2 *o2_3 = new Object2(manager, "O3");

	

	cout << "Object count: " << manager.getObjectCount() << "\n";
	ASSERT_NEQUAL(manager.getObjectCount(), 6, "")

	for (auto& it : manager)
	{
		cout << it->getID() << "\n";
	}

	manager.removeObject(o1_3->getID());
	cout << "Object count: " << manager.getObjectCount() << "\n";
	size_t id = o2_2->getID();
	delete o2_2;
	o2_2 = nullptr;
	if (manager.exists(id))
	{
		cout << "id: " << id << " still exists, but shuld be removed";
	}
	cout << "Object count: " << manager.getObjectCount() << "\n";
	o2_3->freeFromManager();
	cout << "Object count: " << manager.getObjectCount() << "\n";


	DesignPatterns::Object* o2_4 = new DesignPatterns::Object(5);
	if (!manager.addObject(o2_4))
	{
		cout << "Shuld be added \n";
	}
	if (manager.addObject(o2_4))
	{
		cout << "Shuld not be added \n";
	}
	cout << "Object count: " << manager.getObjectCount() << "\n";


	getchar();
	return 0;
}


bool test_fillManager()
{
	DesignPatterns::ObjectManager manager;

	Object1* o1_1 = new Object1(manager, 1);
	Object1* o1_2 = new Object1(manager, 2);
	Object1* o1_3 = new Object1(manager, 3);

	Object2* o2_1 = new Object2(manager, "O1");
	Object2* o2_2 = new Object2(manager, "O2");
	Object2* o2_3 = new Object2(manager, "O3");
	ASSERT_NEQUAL(manager.getObjectCount(), 6, "");

	size_t counter = 0;
	for (auto& it : manager)
	{
		ASSERT_NEQUAL(it->getID(), counter, "");
		++counter;
	}
	
	return true;
}

bool test_getObjects()
{
	DesignPatterns::ObjectManager manager;

	Object1* o1_1 = new Object1(manager, 1);
	Object1* o1_2 = new Object1(manager, 2);
	Object1* o1_3 = new Object1(manager, 3);

	Object2* o2_1 = new Object2(manager, "O1");
	Object2* o2_2 = new Object2(manager, "O2");
	Object2* o2_3 = new Object2(manager, "O3");

	ASSERT_NEQUAL(o1_1, manager.getObject(o1_1->getID()), "");
	ASSERT_NEQUAL(o1_2, manager.getObject(o1_2->getID()), "");
	ASSERT_NEQUAL(o1_3, manager.getObject(o1_3->getID()), "");
	ASSERT_NEQUAL(o2_3, manager.getObject(o2_3->getID()), "");
	ASSERT_TRUE(manager.exists(1560), "");
	ASSERT_NEQUAL(nullptr, manager.getObject(1560), "");
	ASSERT_FALSE(manager.exists(o2_3->getID()), "");
	ASSERT_FALSE(manager.exists(o2_1->getID()), "");
	
	return true;
}
bool test_removeObject()
{
	DesignPatterns::ObjectManager manager;

	Object1* o1_1 = new Object1(manager, 1);
	Object1* o1_2 = new Object1(manager, 2);
	Object1* o1_3 = new Object1(manager, 3);

	Object2* o2_1 = new Object2(manager, "O1");
	Object2* o2_2 = new Object2(manager, "O2");
	Object2* o2_3 = new Object2(manager, "O3");

	ASSERT_NEQUAL(manager.getObjectCount(), 6, "");
	ASSERT_FALSE(manager.removeObject(o1_1->getID()), "Object shuld be in manager, ready to be removed");
	ASSERT_NEQUAL(manager.getObjectCount(), 5, "");
	ASSERT_TRUE(manager.removeObject(o1_1->getID()), "Object shuld be already removed");
	ASSERT_NEQUAL(manager.getObjectCount(), 5, "");

	ASSERT_NEQUAL(o1_2, manager.getObject(o1_2->getID()), "");
	ASSERT_NEQUAL(o1_3, manager.getObject(o1_3->getID()), "");
	ASSERT_NEQUAL(o2_3, manager.getObject(o2_3->getID()), "");
	ASSERT_FALSE(manager.exists(o2_3->getID()), "");
	ASSERT_FALSE(manager.exists(o2_1->getID()), "");
	return true;
}
bool test_doubleInsert()
{

	return true;
}