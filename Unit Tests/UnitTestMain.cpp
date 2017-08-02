//We are going to take over main from CATCH
//We are doing this so we can run CATCH on a seperate thread
//whilst having the window on the main thread
#define CATCH_CONFIG_RUNNER
#include "../CATCH.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>

//Global variables for tests
std::thread* workerThread = nullptr;
std::mutex threadLock;
std::condition_variable conditionalLock;
bool conditionMet = false;

//Forward declare of worker thread function
void WorkerThread(int _argc, char** _argv);

//Provide a definition for this function in your test .cpp
//This gives you the opportunity to do some initialization before the tests are run
//After initialization is complete set conditionMet to true and call notify_all with condition
extern void Initialize(std::condition_variable& _condition, bool& _conditionMet);

//Provide a definition for this function in your test.cpp
//This provides the opportunity to do shutdown opperations before the application closes
extern void Shutdown();

int main(int _argc, char** _argv)
{
	//Kick off the thread
	//This thread will initialize and run CATCH
	workerThread = new std::thread(WorkerThread, _argc, _argv);

	//Initialize the tests
	Initialize(conditionalLock, conditionMet);

	//Wait for CATCH to finish
	workerThread->join();


    //sleep(1.0);
	return 0;
}

//Function definition for WorkerThread
void WorkerThread(int argc, char** argv)
{
	//Wait till condition is met
	std::unique_lock<std::mutex> uniqueLock(threadLock);
	conditionalLock.wait(uniqueLock, []() { return conditionMet; });

	//Let CATCH run itself from this thread
	Catch::Session().run(argc, argv);

	Shutdown();
}