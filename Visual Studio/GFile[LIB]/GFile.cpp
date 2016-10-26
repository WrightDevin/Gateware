
#include "../../Interface/G_System/GFile.h"
#include <fstream>
#include <string>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif


using namespace GW;
using namespace CORE;

class FileIO : public GFile
{
	std::fstream m_file;
	std::string m_currDir;

	unsigned int m_referenceCount;

	public:
		FileIO();
		~FileIO();

		GRETURN OpenForBinaryRead(const char* const _file) override;
		
		GRETURN OpenForBinaryWrite(const char* const _file, GFileOpenFlags _flags) override;

		GRETURN OpenForTextRead(const char* const _file) override;
		
		GRETURN OpenForTextWrite(const char* const _file, GFileOpenFlags _flags) override;

		GRETURN Write(const char* const _inData, unsigned int _numBytes) override;
		
		GRETURN Read(char* _outData, unsigned int _numBytes) override;

		GRETURN WriteLine(const char* const _inData) override;
		
		GRETURN ReadLine(char* _outData, unsigned int _numBytes) override;

		GRETURN CloseFile() override;

		GRETURN SetCurrentWorkingDirectory(const char* const _dir) override;
		//GRETURN GetCurrentWorkingDirectory(char _dir[255]) override;

		GRETURN GetDirectorySize(unsigned int& _outSize) override;
		
		GRETURN GetFilesFromDirectory(char** _outFiles) override;

		GRETURN GetCount(unsigned int &_outCount) override;

		GRETURN IncrementCount() override;

		GRETURN DecrementCount() override;

		GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) override;
};

FileIO::FileIO() : m_referenceCount(1)
{

}

FileIO::~FileIO()
{

}

GRETURN FileIO::OpenForBinaryRead(const char* const _file)
{
	if (m_file.is_open())
		return FAILURE;

	m_file.open(m_currDir + "/" + _file, std::ios::in | std::ios::binary);
	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenForBinaryWrite(const char* const _file, GFileOpenFlags _flags)
{
	if (m_file.is_open())
		return FAILURE;

	if (_flags == APPEND)
	{
		m_file.open(m_currDir + "/" + _file, std::ios::out | std::ios::binary| std::ios::app | std::ios::ate);
		if (!m_file.is_open())
			return FILE_NOT_FOUND;
	}
	else
	{
		m_file.open(m_currDir + "/" + _file, std::ios::out);
		if (!m_file.is_open())
			return FILE_NOT_FOUND;
	}

	return SUCCESS;
}

GRETURN FileIO::OpenForTextRead(const char* const _file)
{
	if (m_file.is_open())
		return FAILURE;

	m_file.open(m_currDir + "/" + _file, std::ios::in);
	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenForTextWrite(const char* const _file, GFileOpenFlags _flags)
{
	if (m_file.is_open())
		return FAILURE;

	if (_flags == APPEND)
	{
		m_file.open(m_currDir + "/" + _file, std::ios::out | std::ios::app | std::ios::ate);
		if (!m_file.is_open())
			return FILE_NOT_FOUND;
	}
	else
	{
		m_file.open(m_currDir + "/" + _file, std::ios::out);
		if (!m_file.is_open())
			return FILE_NOT_FOUND;
	}

	return SUCCESS;
}

GRETURN FileIO::Write(const char* const _inData, unsigned int _numBytes)
{
	if (!m_file.is_open())
		return FAILURE;

	m_file.write(_inData, _numBytes);

	return SUCCESS;
}

GRETURN FileIO::Read(char* _outData, unsigned int _numBytes)
{
	if (!m_file.is_open())
		return FAILURE;

	m_file.read(_outData, _numBytes);
	return SUCCESS;
}

GRETURN FileIO::WriteLine(const char* const _inData)
{
	if (!m_file.is_open())
		return FAILURE;

	m_file << _inData;
	return SUCCESS;
}

GRETURN FileIO::ReadLine(char* _outData, unsigned int _numBytes)
{
	if (!m_file.is_open())
		return FAILURE;

	char buffer[255];
	m_file.getline(buffer, 255);

	strcpy_s(_outData, _numBytes, buffer);

	return SUCCESS;
}

GRETURN FileIO::CloseFile()
{
	m_file.close();
	return SUCCESS;
}

GRETURN FileIO::SetCurrentWorkingDirectory(const char* const _dir)
{
	m_currDir = _dir;
	return SUCCESS;
}

//GRETURN FileIO::GetCurrentWorkingDirectory(char _dir[255])
//{
//
//}

GRETURN FileIO::GetDirectorySize(unsigned int& _outSize)
{
	return SUCCESS;
}

GRETURN FileIO::GetFilesFromDirectory(char** _outFiles)
{
	return SUCCESS;
}

GRETURN FileIO::GetCount(unsigned int &_outCount)
{
	_outCount = m_referenceCount;
	return SUCCESS;
}

GRETURN FileIO::IncrementCount()
{
	ATOMIC_INCREMENT(&m_referenceCount);
	return SUCCESS;
}

GRETURN FileIO::DecrementCount()
{
	unsigned int count = ATOMIC_DECREMENT(&m_referenceCount);
	if (count == 0)
		delete this;

	return SUCCESS;
}

GRETURN FileIO::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface)
{
	return SUCCESS;
}

GRETURN CreateFileHandler(GFile** _outFile)
{
	if (_outFile == nullptr)
		return INVALID_ARGUMENT;

	FileIO* temp = new FileIO();
	if (!temp)
		return FAILURE;

	*_outFile = temp;
	(*_outFile)->IncrementCount();

	return SUCCESS;
}