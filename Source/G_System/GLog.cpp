#include "../../Interface/G_System/GLog.h"
#include "../../Interface/G_System/GFile.h"
#include "GUtility.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <queue> //To queue the messages
#include <thread> //Threading
#include <mutex> //Thread safety
#include <sstream> //Stringstreams
#include <atomic> //Thread safety
#include <iostream> //For cout
#include <cstring>
#include <condition_variable> //For conditional variables

using namespace INTERNAL;
using std::queue;
using std::thread;
using std::string;
using std::mutex;
using std::atomic;
using std::unique_lock;
using std::condition_variable;
using std::cout;

#define MAX_QUEUE_SIZE 20
#define THREAD_SLEEP_TIME 10
#define TIME_BUFFER 40

class LogFile : public GW::CORE::GLog
{
	GW::CORE::GFile* m_logFile;  //Our internal GFile to log to file

	thread* m_worker; //The worker thread we will spin off

	mutex m_queueLock; //queuelock for locking the queue we are logging to

	queue<string> m_logQueue; //The queue we will log to

	bool m_isVerbose;  //Verbose logging boolean

	bool m_isConsoleLogged; //Console loggong boolean

	atomic<bool> m_threadRunning; //Boolean to kill the thread

	atomic<unsigned int> m_refCount; //Referance counter

	condition_variable m_conditional;

public:
    LogFile();
    virtual ~LogFile();

	GW::GRETURN Init(const char* const _fileName);

	GW::GRETURN Init(GW::CORE::GFile* _file);

	GW::GRETURN Log(const char* const _log) override;

	GW::GRETURN LogCatergorized(const char* const _category, const char* const _log) override;

	void EnableVerboseLogging(bool _value) override;

	void EnableConsoleLogging(bool _value) override;

	GW::GRETURN Flush() override;

	GW::GRETURN GetCount(unsigned int &_outCount) override;

	GW::GRETURN IncrementCount() override;

	GW::GRETURN DecrementCount() override;

	GW::GRETURN RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface) override;

private:
	void LogWorker(); //Our worker thread function

	unsigned long long GetThreadID(); //Gets the thread ID
};

LogFile::LogFile() : m_refCount(1)
{
	m_isConsoleLogged = false;
	m_isVerbose = true;
}

LogFile::~LogFile()
{
}

GW::GRETURN LogFile::Init(const char* const _fileName)
{
	//Create a GFile
	GW::GRETURN rv = GCreateFile(&m_logFile);
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
	return GW::SUCCESS;
}

GW::GRETURN LogFile::Init(GW::CORE::GFile* _file)
{
	//Check to ensure valid GFile
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Set the GFile and increment the ref count
	m_logFile = _file;
	m_logFile->IncrementCount();

	//Fire off worker thread
	m_threadRunning = true;
	m_worker = new thread(&LogFile::LogWorker, this);

	//m_isVerbose is defaulted to true
	m_isVerbose = true;
	return GW::SUCCESS;
}

GW::GRETURN LogFile::Log(const char* const _log)
{
	if (_log == nullptr)
		return GW::INVALID_ARGUMENT;

	std::stringstream logStream;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		time_t t = time(0);   // get time now
		char timeBuffer[TIME_BUFFER];

#if defined(_WIN32)
		//Parse the time out to readable time
		struct tm buf;
		localtime_s(&buf, &t);
		asctime_s(timeBuffer, TIME_BUFFER, &buf);

#elif defined(__APPLE__) || defined(__linux__)
		//Parse the time out to readable time
		string buffer(asctime(localtime(&t)));
		strcpy_s(timeBuffer, TIME_BUFFER, buffer.c_str());

#endif
		//Get rid of new line added by asctime
		timeBuffer[strlen(timeBuffer) - 1] = '\0';

		//Create our log string
        logStream << "[" << timeBuffer << "] ThreadID[";
		logStream << GetThreadID() << "]\t";
	}

	//Add the log and a newline
	logStream << _log << "\r\n";

	//Lock the mutex to push the new msg
	m_queueLock.lock();

	//Check to see if we are at our max messages
	if (m_logQueue.size() >= MAX_QUEUE_SIZE)
	{
		m_queueLock.unlock();
		return GW::FAILURE;
	}

	//Push the message to the queue
	m_logQueue.push(logStream.str());

	if (m_isConsoleLogged)
		cout << logStream.str();

#if defined(_MSC_VER)
	OutputDebugStringW(G_TO_UTF16(logStream.str()).c_str());
#endif


	m_queueLock.unlock();

	return GW::SUCCESS;
}

GW::GRETURN LogFile::LogCatergorized(const char* const _category, const char* const _log)
{
	if (_category == nullptr || _log == nullptr)
		return GW::INVALID_ARGUMENT;

	//The stream that will contain the full message
	std::stringstream logStream;

	//Check verbose logging and add the verbose info if on
	if (m_isVerbose)
	{
		time_t t = time(0);   // get time now
		char timeBuffer[TIME_BUFFER];

	#if defined(_WIN32)

		//Parse time to readable time
		struct tm buf;
		localtime_s(&buf, &t);
		asctime_s(timeBuffer, TIME_BUFFER, &buf);

    #elif defined(__APPLE__) || defined(__linux__)

		//Parse time to readable time
		string buffer(asctime(localtime(&t)));
		strcpy_s(timeBuffer, TIME_BUFFER, buffer.c_str());

	#endif
		//Get rid of new line added by asctime
		timeBuffer[strlen(timeBuffer) - 1] = '\0';

		//Build the string
        logStream << "[" << timeBuffer << "] ThreadID[";
		logStream << GetThreadID() << "]\t";
	}

	//Add the category and message
	logStream << "[" << _category << "]\t" << _log << "\r\n";

	//Lock the mutex to push the new msg
	m_queueLock.lock();

	//Check to see if we are at our max messages
	if (m_logQueue.size() >= MAX_QUEUE_SIZE)
	{
		m_queueLock.unlock();
		return GW::FAILURE;
	}

	//Push the message to the queue
	m_logQueue.push(logStream.str());

	if (m_isConsoleLogged)
		cout << logStream.str();

#if defined(_MSC_VER)
	OutputDebugStringW(G_TO_UTF16(logStream.str()).c_str());
#endif

	m_queueLock.unlock();

	return GW::SUCCESS;
}

void LogFile::EnableVerboseLogging(bool _value)
{
	//Set the verbose boolean
	m_isVerbose = _value;
}

void LogFile::EnableConsoleLogging(bool _value)
{
	//Set the console logging boolean
	m_isConsoleLogged = _value;
}

GW::GRETURN LogFile::Flush()
{
	m_conditional.notify_all();

	//Flush the file
	return GW::SUCCESS;
}

unsigned long long LogFile::GetThreadID()
{
	//Get the thread ID and store it in a stringstream
	std::stringstream ss;
	ss << std::this_thread::get_id();

	//Convert the string sequence to an unsigned long long
	return std::stoull(ss.str());
}

GW::GRETURN LogFile::GetCount(unsigned int &_outCount)
{
	_outCount = m_refCount;
	return GW::SUCCESS;
}

GW::GRETURN LogFile::IncrementCount()
{
	//Check for possible overflow
	if (m_refCount == G_UINT_MAX)
		return GW::FAILURE;

	//Increment the count
	++m_refCount;

	return GW::SUCCESS;
}

GW::GRETURN LogFile::DecrementCount()
{
	//Check for possible underflow
	if (m_refCount == 0)
		return GW::FAILURE;

	//Decrement the count
	--m_refCount;

	//Make sure the object should still exist
	//Delete it if not
	if (m_refCount == 0)
	{
		//Decrement the count of our internal GFile
		m_logFile->DecrementCount();

		//Tell the thread to stop running and wait for it
		m_threadRunning = false;
		m_worker->join();

		//Cleanup;
		delete m_worker;
		delete this;
	}

	return GW::SUCCESS;
}

GW::GRETURN LogFile::RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return GW::INVALID_ARGUMENT;

	//If interface == this
	if (_interfaceID == GW::CORE::GLogUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GLog* convert = reinterpret_cast<GLog*>(this);

		//Increment the count of the GFile.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is multithreaded.
	else if (_interfaceID == GW::CORE::GMultiThreadedUUIID)
	{
		//Temportary GMultiThreaded* to ensure proper functions are called
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);

		//Increment the count of the GMultithreaded.
		convert->IncrementCount();

		//Store the value.
		(*_outputInterface) = convert;
	}
	//If requested interface is the primary interface.
	else if (_interfaceID == GW::CORE::GInterfaceUUIID)
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
		return GW::INTERFACE_UNSUPPORTED;

	return GW::SUCCESS;
}

GW::GRETURN GW::CORE::GCreateLog(const char* const _fileName, GLog** _outLog)
{
	//Check to make sure the user passed a valid pointer
	if (_outLog == nullptr)
		return GW::INVALID_ARGUMENT;

	//Create a new LogFile
	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return GW::FAILURE;

	//Init the log file
	GW::GRETURN rv = logFile->Init(_fileName);
	if (G_FAIL(rv))
		return rv;

	//Store new log file in passed in pointer
	(*_outLog) = logFile;

	return GW::SUCCESS;
}

GW::GRETURN GW::CORE::GCreateLog(GFile* _file, GLog** _outLog)
{
	//Check to make sure the user passed a valid pointer
	if (_outLog == nullptr)
		return GW::INVALID_ARGUMENT;

	//Create a new LogFile
	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return GW::FAILURE;

	//Init the log file
	GW::GRETURN rv = logFile->Init(_file);
	if (G_FAIL(rv))
		return rv;

	//Store new log file in passed in pointer
	(*_outLog) = logFile;

	return GW::SUCCESS;
}

//LogWorker is the function that the logging thread will run. This thread will also control
//the closing of GFile when the log is destroyed
void LogFile::LogWorker()
{
	unique_lock<mutex> queueLock(m_queueLock);
	while (m_threadRunning)
	{
		//Will lock the mutex when awaken and unlock it when put back to sleep
		m_conditional.wait_for(queueLock, std::chrono::seconds(20));

		//If there is anything to write
		if (m_logQueue.size() != 0)
		{
			//Swap the queue to another queue so we don't have to worry about thread safety
			queue<string> writeQueue;
			writeQueue.swap(m_logQueue);

			queueLock.unlock();

			//Write out the new queue
			for (unsigned int i = 0; i < writeQueue.size(); ++i)
			{
				m_logFile->WriteLine(writeQueue.front().c_str());
				writeQueue.pop();

				m_logFile->FlushFile();
			}
		}
	}

	//Close the file
	m_logFile->CloseFile();
}
