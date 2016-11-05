#include "../../Interface/G_System/GLog.h"
#include "../../Interface/G_System/GFile.h"


#include <queue>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <atomic>
#include <iostream>

using namespace GW;
using namespace CORE;
using std::queue;
using std::thread;
using std::string;
using std::mutex;
using std::atomic;
using std::cout;

#define MAX_QUEUE_SIZE 20
#define THREAD_SLEEP_TIME 10
#define G_UINT_MAX 0xffffffff

//Nameless namespace to contain the worker thread function

class LogFile : public GLog
{
	GFile* m_logFile;

	thread* m_worker;

	mutex m_queueLock;

	queue<string> m_logQueue;

	bool m_isVerbose;

	bool m_isConsoleLogged;

	atomic<bool> m_threadRunning;

	atomic<unsigned int> m_refCount;

public:
    LogFile();
    virtual ~LogFile();

	GRETURN Init(const char* const _fileName);

	GRETURN Init(GFile* _file);

	GRETURN Log(const char* const _log) override;

	GRETURN LogCatergorized(const char* const _category, const char* const _log) override;

	void EnableVerboseLogging(bool _value) override;

	void EnableConsoleLogging(bool _value) override;

	GRETURN Flush() override;

	GRETURN CloseLogs() override;

	GRETURN GetCount(unsigned int &_outCount) override;

	GRETURN IncrementCount() override;

	GRETURN DecrementCount() override;

	GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) override;

	void LogWorker();

private:
	unsigned int GetThreadID();
};

LogFile::LogFile() : m_refCount(1)
{
	m_isConsoleLogged = false;
	m_isVerbose = true;
}

LogFile::~LogFile()
{
}

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

	//Fire off worker thread
	m_threadRunning = true;
	m_worker = new thread(&LogFile::LogWorker, this);

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

	//Fire off worker thread
	m_threadRunning = true;
	m_worker = new thread(&LogFile::LogWorker, this);

	//m_isVerbose is defaulted to true
	m_isVerbose = true;
	return SUCCESS;
}

GRETURN LogFile::Log(const char* const _log)
{
	string logString;
	std::stringstream logStream;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);

		logStream << "[" << (now->tm_year + 1900) << '/' << (now->tm_mon + 1) << '/' << now->tm_mday << " ";
		logStream << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " [";
		logStream << GetThreadID() << "]\t";

	}

	//Add the log and a newline
	logStream << _log << "\r\n";
	logString = logStream.str();

	//Lock the mutex to push the new msg
	m_queueLock.lock();

	//Check to see if we are at our max messages
	if (m_logQueue.size() >= MAX_QUEUE_SIZE)
	{
		m_queueLock.unlock();
		return FAILURE;
	}

	if (m_isConsoleLogged)
		cout << logString;

	//Push the message to the queue
	m_logQueue.push(logString);

	m_queueLock.unlock();

	return SUCCESS;
}

GRETURN LogFile::LogCatergorized(const char* const _category, const char* const _log)
{
	string logString;
	std::stringstream logStream;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);

		logStream << "[" << (now->tm_year + 1900) << '/' << (now->tm_mon + 1) << '/' << now->tm_mday << " ";
		logStream << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " [";
		logStream << GetThreadID() << "] ";
	}

	//Add the category and message
	logStream << "[" << _category << "]\t" << _log << "\r\n";
	logString = logStream.str();

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

	if (m_isConsoleLogged)
		cout << logString;

	m_queueLock.unlock();

	return SUCCESS;
}

void LogFile::EnableVerboseLogging(bool _value)
{
	m_isVerbose = _value;
}

void LogFile::EnableConsoleLogging(bool _value)
{
	m_isConsoleLogged = _value;
}

GRETURN LogFile::Flush()
{
	return m_logFile->FlushFile();
}

GRETURN LogFile::CloseLogs()
{
	Flush();

	return SUCCESS;
}

unsigned int LogFile::GetThreadID()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return (unsigned int)std::stoull(ss.str());
}

GRETURN LogFile::GetCount(unsigned int &_outCount)
{
	_outCount = m_refCount;
	return SUCCESS;
}

GRETURN LogFile::IncrementCount()
{
	//Check for possible overflow
	if (m_refCount == G_UINT_MAX)
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
		m_threadRunning = false;
		m_worker->join();
		m_logFile->DecrementCount();
		delete m_worker;
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

//LogWorker is the function that the logging thread will run. This thread will also control
//the closing of GFile when the log is destroyed
void LogFile::LogWorker()
{
	while (m_threadRunning)
	{
		//We use a try lock here so that we don't take a lot of time locking
		if (m_queueLock.try_lock())
		{
			//If there is anything to write
			if (m_logQueue.size() != 0)
			{
				//Swap the queue to another queue so we don't have to worry about thread safety
				queue<string> writeQueue;
				writeQueue.swap(m_logQueue);

				m_queueLock.unlock();

				//Write out the new queue
				for (unsigned int i = 0; i < writeQueue.size(); ++i)
				{
					m_logFile->WriteLine(writeQueue.front().c_str());
					writeQueue.pop();

					m_logFile->FlushFile();
				}
			}
			else
				m_queueLock.unlock();
		}

		//Sleep for 10 seconds
		std::this_thread::sleep_for(std::chrono::seconds(THREAD_SLEEP_TIME));
	}

	//Close the file
	m_logFile->CloseFile();
}
