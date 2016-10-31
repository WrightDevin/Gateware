#include "../../Interface/G_System/GLog.h"
#include "../../Interface/G_System/GFile.h"

#include <queue>
#include <thread>
#include <mutex>
#include <string>

using namespace GW;
using namespace CORE;
using std::queue;
using std::thread;
using std::string;
using std::mutex;

//Nameless namespace to contain the worker thread function
namespace
{
	void LogWorker(GFile* _file, queue<string>& _queue, mutex& _queueLock, bool& _running)
	{
		while (_running)
		{
			if (_queueLock.try_lock())
			{
				if (_queue.size() != 0)
				{
					queue<string> writeQueue;
					writeQueue.swap(_queue);

					_queueLock.unlock();

					for (int i = 0; i < writeQueue.size(); ++i)
					{
						_file->WriteLine(writeQueue.front().c_str());
						writeQueue.pop();

						//TODO: Flush after write
					}
				}
				else
					_queueLock.unlock();
			}

			//Sleep for 10 seconds
			std::this_thread::sleep_for(std::chrono::seconds(10));
		}

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
	if (G_FAIL(GCreateFileHandler(&m_logFile)))
		return FAILURE;

	if (G_FAIL(m_logFile->OpenForTextWrite(_fileName, APPEND)))
		return FAILURE;

	//TODO: Fire off worker thread

	m_isVerbose = true;
	return SUCCESS;
}

GRETURN LogFile::Init(GFile* _file)
{
	if (_file == nullptr)
		return INVALID_ARGUMENT;

	m_logFile = _file;
	m_logFile->IncrementCount();

	//TODO: Fire off worker thread

	m_isVerbose = true;
	return SUCCESS;
}

GRETURN LogFile::Log(const char* const _log)
{
	string logString;

	if (m_isVerbose)
	{
		//TODO: Create log string with date, time, threadID
	}
	else
	{
		logString = _log;
		logString += "\r\n";
	}

	m_queueLock.lock();
	if (m_logQueue.size() >= 20)
	{
		m_queueLock.unlock();
		return FAILURE;
	}


	m_logQueue.push(logString);

	m_queueLock.unlock();

	return SUCCESS;
}

GRETURN LogFile::LogCatergorized(const char* const _category, const char* const _log)
{
	string logString;

	if (m_isVerbose)
	{
		//TODO: Create log string with date, time, threadID
	}
	else
	{
		logString = "[";
		logString += _category;
		logString += "] ";
		logString += _log;
		logString += "\r\n";
	}

	m_queueLock.lock();
	if (m_logQueue.size() >= 20)
	{
		m_queueLock.unlock();
		return FAILURE;
	}


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

	return SUCCESS;
}

GRETURN LogFile::IncrementCount()
{
	return SUCCESS;
}

GRETURN LogFile::DecrementCount()
{
	return SUCCESS;
}

GRETURN LogFile::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GFileUUIID)
	{
		GLog* convert = reinterpret_cast<GLog*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GMultiThreadedUUIID)
	{
		GMultiThreaded* convert = reinterpret_cast<GMultiThreaded*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else if (_interfaceID == GInterfaceUUIID)
	{
		GInterface* convert = reinterpret_cast<GInterface*>(this);
		convert->IncrementCount();
		(*_outputInterface) = convert;
	}
	else
		return INTERFACE_UNSUPPORTED;

	return SUCCESS;
}

GRETURN GCreateLog(const char* const _fileName, GLog** _outLog)
{
	if (_outLog == nullptr)
		return FAILURE;

	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return FAILURE;

	GRETURN rv = logFile->Init(_fileName);
	if (G_FAIL(rv))
		return rv;

	(*_outLog) = logFile;

	return SUCCESS;
}

GRETURN GCreateLog(GFile* _file, GLog** _outLog)
{
	if (_outLog == nullptr)
		return FAILURE;

	LogFile* logFile = new LogFile();
	if (logFile == nullptr)
		return FAILURE;

	GRETURN rv = logFile->Init(_file);
	if (G_FAIL(rv))
		return rv;

	(*_outLog) = logFile;

	return SUCCESS;
}