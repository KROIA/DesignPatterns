#include "../exampleHelper.h"
#include "Object1.h"
#include "Object2.h"
#include <fstream>
#include <vector>
#include <string>


const Example::Info Example::info =
{
	"ObjectManager",
	"This is a example to show the usage of the ObjectManager"
};

using std::cout;
template<typename T>
void saveAsCSV(const std::vector<std::vector<T>>& data, 
			   const std::vector<std::string>& headers, 
			   const std::string& filename);
template<typename T>
void saveBatchedAsCSV(const std::vector<T>& values, size_t batchSize,
				      const std::string &unit, const std::string& filename); // unit (time, length ...)

bool test_fillManager();
bool test_getObjects();
bool test_removeObject();
bool test_doubleInsert();
bool test_performance_objectAdd(DesignPatterns::ObjectManager &manager);
bool test_performance_objectSearch(DesignPatterns::ObjectManager &manager);
bool test_performance_objectRemove(DesignPatterns::ObjectManager &manager);


int main(int argc, char* argv[])
{
	Example::init();
	UnitTest::reset();

	
	TEST_RUN(test_fillManager);
	TEST_RUN(test_removeObject);
	TEST_RUN(test_doubleInsert);

	DesignPatterns::ObjectManager manager;
	TEST_RUN(test_performance_objectAdd, manager);
	TEST_RUN(test_performance_objectSearch, manager);
	TEST_RUN(test_performance_objectRemove, manager);


	UnitTest::printResults();
	getchar();
	return 0;
}

template<typename T>
void saveAsCSV(const std::vector<std::vector<T>>& data,
	           const std::vector<std::string>& headers, 
	           const std::string& filename) 
{
	UnitTest::print("Save file: "+filename, UnitTest::Color::white);
	std::ofstream file(filename);
	if (!file.is_open())
	{
		UnitTest::printLn("  fail, can't open file", UnitTest::Color::red);
		return;
	}

	// Write headers
	for (const auto& header : headers) {
		file << header << ";";
	}
	file << std::endl;

	// Write data
	for (size_t row = 0; row < data[0].size(); row++) {
		for (size_t col = 0; col < data.size(); col++) {
			std::string nr = std::to_string(data[col][row]);
			size_t pos = nr.find(".");
			if (pos != std::string::npos)
			{
				nr[pos] = ',';
			}
			file << nr << ";";
		}
		file << std::endl;
	}
	file.close();

	UnitTest::printLn("  done", UnitTest::Color::green);
}

template<typename T>
void saveBatchedAsCSV(const std::vector<T>& values, size_t batchSize,
	                  const std::string& unit, const std::string& filename)
{
	std::vector<T> batchedAverage;
	std::vector<T> batchedMin;
	std::vector<T> batchedMax;


	size_t batches = values.size() / batchSize;
	batchedAverage.reserve(batches);
	batchedMin.reserve(batches);
	batchedMax.reserve(batches);
	size_t index = 0;
	for (size_t i = 0; i < batches; ++i)
	{
		T min = values[index];
		T max = values[index];
		T average = values[index];
		++index;
		for (size_t j = 1; j < batchSize; ++j)
		{
			T value = values[index];
			average += value;
			if (min > value)
				min = value;
			if (max < value)
				max = value;
			++index;
		}
		batchedAverage.push_back(average / (T)batchSize);
		batchedMin.push_back(min);
		batchedMax.push_back(max);
	}


	saveAsCSV<T>({ batchedMin, batchedMax, batchedAverage }, { "min "+ unit, "max "+ unit, "average "+ unit }, filename);
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
	Object2* o2_1 = nullptr;
	Object2* o2_2 = nullptr;
	Object2* o2_3 = nullptr;
	{
		DesignPatterns::ObjectManager manager;

		Object1* o1_1 = new Object1(manager, 1);
		Object1* o1_2 = new Object1(manager, 2);
		Object1* o1_3 = new Object1(manager, 3);

		o2_1 = new Object2(manager, "O1");
		o2_2 = new Object2(manager, "O2");
		o2_3 = new Object2(manager, "O3");

		ASSERT_NEQUAL(manager.getObjectCount(), 6, "");
		ASSERT_FALSE(manager.removeObject(o1_1->getID()), "Object should be in manager, ready to be removed");
		ASSERT_NEQUAL(manager.getObjectCount(), 5, "");
		ASSERT_TRUE(manager.removeObject(o1_1->getID()), "Object should be already removed");
		ASSERT_NEQUAL(manager.getObjectCount(), 5, "");

		size_t id = o1_2->getID();
		ASSERT_FALSE(manager.removeObject(id), "");
		delete o1_2;
		o1_2 = nullptr;
		ASSERT_TRUE(manager.removeObject(id), "should be removed because the object got destroyed");
		ASSERT_NEQUAL(manager.getObjectCount(), 4, "");

		ASSERT_NEQUAL(o2_1->getManager(), &manager, "");
		ASSERT_NEQUAL(o2_2->getManager(), &manager, "");
		ASSERT_NEQUAL(o2_3->getManager(), &manager, "");
		manager.clear();
		ASSERT_NEQUAL(manager.getObjectCount(), 0, "Manager should be cleared");
		ASSERT_NEQUAL(o2_1->getManager(), nullptr, "Manager should be set to nullptr");
		ASSERT_NEQUAL(o2_2->getManager(), nullptr, "Manager should be set to nullptr");
		ASSERT_NEQUAL(o2_3->getManager(), nullptr, "Manager should be set to nullptr");

		ASSERT_FALSE(manager.addObject(o2_1), "");
		ASSERT_FALSE(manager.addObject(o2_2), "");
		ASSERT_FALSE(manager.addObject(o2_3), "");

		ASSERT_NEQUAL(o2_1->getManager(), &manager, "");
		ASSERT_NEQUAL(o2_2->getManager(), &manager, "");
		ASSERT_NEQUAL(o2_3->getManager(), &manager, "");
	}
	ASSERT_NEQUAL(o2_1->getManager(), nullptr, "Manager should be set to nullptr");
	ASSERT_NEQUAL(o2_2->getManager(), nullptr, "Manager should be set to nullptr");
	ASSERT_NEQUAL(o2_3->getManager(), nullptr, "Manager should be set to nullptr");


	return true;
}
bool test_doubleInsert()
{
	DesignPatterns::ObjectManager manager;

	Object1* o1_1 = new Object1(manager, 1);
	Object1* o1_2 = new Object1(manager, 2);
	Object1* o1_3 = new Object1(manager, 3);

	Object2* o2_1 = new Object2(manager, "O1");
	Object2* o2_2 = new Object2(manager, "O2");
	Object2* o2_3 = new Object2(manager, "O3");
	ASSERT_NEQUAL(manager.getObjectCount(), 6, "");

	ASSERT_TRUE(manager.addObject(o1_1), "Shuld not be added, because it already is in manager");
	ASSERT_NEQUAL(manager.getObjectCount(), 6, "");
	ASSERT_TRUE(manager.addObject(o1_2), "Shuld not be added, because it already is in manager");
	ASSERT_TRUE(manager.addObject(o2_3), "Shuld not be added, because it already is in manager");
	ASSERT_NEQUAL(manager.getObjectCount(), 6, "");

	return true;
}

bool test_performance_objectAdd(DesignPatterns::ObjectManager &manager)
{
	size_t objectCount = 100000000;
	std::vector<double> times;
	std::vector<Object1*> objs;
	times.reserve(objectCount);
	objs.reserve(objectCount);
	{
		UnitTest::print("Instantiate " + std::to_string(objectCount) + " objects... ", UnitTest::Color::yellow);
		DesignPatterns::PerformanceTimer timer;
		timer.start();
		for (size_t i = 0; i < objectCount; ++i)
		{
			objs.push_back(new Object1(i, 1));
		}
		timer.stop();
		UnitTest::printLn("done. " + std::to_string(timer.elapsed_micros()) + "us", UnitTest::Color::green);
	}

	long long timeNanos = 0;
	long long timeNanosSum = 0;
	UnitTest::print("Fill manager... ", UnitTest::Color::yellow);
	for (size_t i = 0; i < objs.size(); ++i)
	{		
		clock_t t1 = clock();
		{
			DesignPatterns::PerformanceTimer timer(timeNanos);
			ASSERT_FALSE(manager.addObject(objs[i]), "Object with ID: "+std::to_string(objs[i]->getID()));
		}
		times.push_back(timeNanos);
		timeNanosSum += timeNanos;
		timeNanos = 0;
	}
	UnitTest::printLn("done. " + std::to_string(timeNanosSum*0.001) + "us", UnitTest::Color::green);
	saveBatchedAsCSV(times, objectCount/100, "us", "test_performance_objectAdd.csv");
	return true;
}
bool test_performance_objectSearch(DesignPatterns::ObjectManager& manager)
{
	size_t objectCount = manager.getObjectCount();
	size_t searches = 100000000;

	std::vector<double> times;
	long long timeNanos = 0;
	long long timeNanosSum = 0;
	UnitTest::print("Search objects in manager... ", UnitTest::Color::yellow);
	for (size_t i = 0; i < searches; ++i)
	{
		size_t searchedID = rand() % objectCount;
		{
			DesignPatterns::PerformanceTimer timer(timeNanos);
			DesignPatterns::Object* obj = manager.getObject(searchedID);
			ASSERT_EQUAL(obj, nullptr, "");
			ASSERT_NEQUAL(obj->getID(), searchedID);
		}
		times.push_back(timeNanos);
		timeNanosSum += timeNanos;
		timeNanos = 0;
	}
	UnitTest::printLn("done. " + std::to_string(timeNanosSum * 0.001) + "us", UnitTest::Color::green);
	saveBatchedAsCSV(times, searches/100, "us", "test_performance_objectSearch.csv");
	return true;
}
bool test_performance_objectRemove(DesignPatterns::ObjectManager& manager)
{
	return true;
}