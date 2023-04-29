#include "exampleHelper.h"
#include "Tests/TestPerformanceTimer.h"
#include "Tests/TestInfo.h"
#include "Tests/TestObjectManager.h"
#include "Tests/TestSingelton.h"

//#define PERFORMANCE_TEST


const Example::Info Example::info =
{
	"UnitTests",
	"UnitTests for the library"
};

int main(int argc, char* argv[])
{
	Example::init();

	UnitTest::TestRunner runner;
	runner.addTest(new TestInfo());
	runner.addTest(new TestPerformanceTimer());
#ifdef PERFORMANCE_TEST
	runner.addTest(new TestObjectManager(100000000));
#else
	runner.addTest(new TestObjectManager(1000));
#endif
	runner.addTest(new TestSingelton());
	


	bool pass = runner.runTests();
	runner.printResults();


	getchar();
	return pass;
}

