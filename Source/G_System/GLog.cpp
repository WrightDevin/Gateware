#include "../../Interface/G_System/GLog.h"
#include "../../Interface/G_System/GFile.h"


#include <queue>
#include <thread>
#include <mutex>
#include <string>
#include <atomic>

using namespace GW;
using namespace CORE;
using std::queue;
using std::thread;
using std::string;
using std::mutex;
using std::atomic;

#define MAX_QUEUE_SIZE 20
#define THREAD_SLEEP_TIME 10

//Nameless namespace to contain the worker thread function
namespace
{
	//LogWorker is the function that the logging thread will run. This thread will also control
	//the closing of GFile when the log is destroyed
	void LogWorker(GFile* _file, queue<string>& _queue, mutex& _queueLock, bool& _running)
	{
		while (_running)
		{
			//We use a try lock here so that we don't take a lot of time locking
			if (_queueLock.try_lock())
			{
				//If there is anything to write
				if (_queue.size() != 0)
				{
					//Swap the queue to another queue so we don't have to worry about thread safety
					queue<string> writeQueue;
					writeQueue.swap(_queue);

					_queueLock.unlock();

					//Write out the new queue
					for (unsigned int i = 0; i < writeQueue.size(); ++i)
					{
						_file->WriteLine(writeQueue.front().c_str());
						writeQueue.pop();

						//TODO: Flush after write (Need this ability in GFile)
					}
				}
				else
					_queueLock.unlock();
			}

			//Sleep for 10 seconds
			std::this_thread::sleep_for(std::chrono::seconds(THREAD_SLEEP_TIME));
		}

		//Close the file
		_file->CloseFile();
	}
}

class LogFile : public GLog
{
	GFile* m_logFile;

	thread m_workerThread;
	
	mutex m_queueLock;

	queue<string> m_logQueue;
	
	bool m_isVerbose;

	atomic<unsigned int> m_refCount;

public:
	GRETURN Init(const char* const _fileName);

	GRETURN Init(GFile* _file);

	GRETURN Log(const char* const _log) override;

	GRETURN LogCatergorized(const char* const _category, const char* const _log) override;

	void EnableVerboseLogging(bool _value) override;

	GRETURN Flush() override;

	GRETURN CloseLogs() override;

	GRETURN GetCount(unsigned int &_outCount) override;
	
	GRETURN IncrementCount() override;
	
	GRETURN DecrementCount() override;
	
	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) override;
};

GRETURN LogFile::Init(const char* const _fileName)
{
	//Create a GFile
	GRETURN rv = CreateGFile(&m_logFile);
	if (G_FAIL(rv))
		return rv;

	//Open the GFile for text write out appending the write out
	rv = m_logFile->AppendTextWrite(_fileName);
	if (G_FAIL(rv))
		return rv;

	//TODO: Fire off worker thread

	//m_isVerbose is defaulted to true
	m_isVerbose = true;
	return SUCCESS;
}

GRETURN LogFile::Init(GFile* _file)
{
	//Check to ensure valid GFile
	if (_file == nullptr)
		return INVALID_ARGUMENT;

	//Set the GFile and increment the ref count
	m_logFile = _file;
	m_logFile->IncrementCount();

	//TODO: Fire off worker thread

	//m_isVerbose is defaulted to true
	m_isVerbose = true;
	return SUCCESS;
}

GRETURN LogFile::Log(const char* const _log)
{
	string logString;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		//TODO: Create log string with date, time, threadID
	}

	//Add the log and a newline
	logString += _log;
	logString += "\r\n";

	//Lock the mutex to push the new msg
	m_queueLock.lock();

	//Check to see if we are at our max messages
	if (m_logQueue.size() >= MAX_QUEUE_SIZE)
	{
		m_queueLock.unlock();
		return FAILURE;
	}

	//Push the message to the queue
	m_logQueue.push(logString);

	m_queueLock.unlock();

	return SUCCESS;
}

GRETURN LogFile::LogCatergorized(const char* const _category, const char* const _log)
{
	string logString;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		//TODO: Create log string with date, time, threadID
	}

	//Add the category and message
	logString += "[";
	logString += _category;
	logString += "]\t";
	logString += _log;
	logString += "\r\n";

	//Lock the mutex to push the new msg
	m_queueLock.lock();

	//Check to see if we are at our max messages
	if (m_logQueue.size() >= MAX_QUEUE_SIZE)
	{
		m_queueLock.unlock();
		return FAILURE;
	}

	//Push the message to the queue
	m_logQueue.push(logString);

	m_queueLock.unlock();

	return SUCCESS;
}

void LogFile::EnableVerboseLogging(bool _value)
{
	m_isVerbose = _value;
}

GRETURN LogFile::Flush()
{
	//TODO: Implement function. GFile has no functionality for this atm

	return SUCCESS;
}

GRETURN LogFile::CloseLogs()
{
	Flush();

	//TODO: Send quit message to worker thread

	return SUCCESS;
}

GRETURN LogFile::GetCount(unsigned int &_outCount)
{
	_outCount = m_refCount;
	return SUCCESS;
}

GRETURN LogFile::IncrementCount()
{
	//Check for possible overflow
	if (m_refCount == UINT_MAX)
		return FAILURE;

	//Increment the count
	++m_refCount;

	return SUCCESS;
}

GRETURN LogFile::DecrementCount()
{
	//Check for possible underflow
	if (m_refCount == 0)
		return FAILURE;

	//Decrement the count
	--m_refCount;

	//Make sure the object should still exist
	//Delete it if not
	if (m_refCount == 0)
	{
		m_workerThread.join();
		delete this;
	}

	return SUCCESS;
}

GRETURN LogFile::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	//If interface == this
	if (_interfaceID == GLogUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GLog* convert = reinterpret_cast<GLog*>(this);

		//Increment the count of the GFile.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is multithreaded.
	else if (_interfaceID == GMultiThreadedUUIID)
	{
		//Temportary GMultiThreaded* to ensure proper functions are called
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);

		//Increment the count of the GMultithreaded.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is the primary interface.
	else if (_interfaceID == GInterfaceUUIID)
	{
		//Temporary GInterface* to ensure proper functions are called.
		GInterface* convert = reinterpret_cast<GInterface*>(this);

		//Increment the count of the GInterface.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//Interface is not supported
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GRETURN GCreateLog(const char* const _fileName, GLog** _outLog)
{
	//Check to make sure the user passed a valid pointer
	if (_outLog == nullptr)
		return INVALID_ARGUMENT;

	//Create a new LogFile
	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return FAILURE;

	//Init the log file
	GRETURN rv = logFile->Init(_fileName);
	if (G_FAIL(rv))
		return rv;

	//Store new log file in passed in pointer
	(*_outLog) = logFile;

	return SUCCESS;
}

GRETURN GCreateLog(GFile* _file, GLog** _outLog)
{
	//Check to make sure the user passed a valid pointer
	if (_outLog == nullptr)
		return INVALID_ARGUMENT;

	//Create a new LogFile
	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return FAILURE;

	//Init the log file
	GRETURN rv = logFile->Init(_file);
	if (G_FAIL(rv))
		return rv;

	//Store new log file in passed in pointer
	(*_outLog) = logFile;

	return SUCCESS;
}