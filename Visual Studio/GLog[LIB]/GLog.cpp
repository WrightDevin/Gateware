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

class LogFile : public GLog
{
	thread m_workerThread;
	queue<string> m_logQueue;
	mutex m_queueLock;

	GFile* m_logFile;

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
	if (FAILED(GCreateFileHandler(&m_logFile)))
		return FAILURE;

	if (FAILED(m_logFile->OpenForTextWrite(_fileName, APPEND)))
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
	return SUCCESS;
}

GRETURN GCreateLog(const char* const _fileName, GLog** _outLog)
{
	if (_outLog == nullptr)
		return FAILURE;

	LogFile* temp = new LogFile();
	if (temp == nullptr)
		return FAILURE;

	if (FAILED(temp->Init(_fileName)))
		return FAILURE;

	(*_outLog) = temp;

	return SUCCESS;
}

GRETURN GCreateLog(GFile* _file, GLog** _outLog)
{
	if (_outLog == nullptr)
		return FAILURE;

	LogFile* temp = new LogFile();
	if (temp == nullptr)
		return FAILURE;

	if (FAILED(temp->Init(_file)))
		return FAILURE;

	(*_outLog) = temp;

	return SUCCESS;
}