
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
using std::fstream;
using std::ios;

class FileIO : public GFile
{
	DIR* m_currDir;
	fstream m_file;

	unsigned int m_refCount;

	public:
		FileIO();
		~FileIO();

		GRETURN Init();

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
		
		GRETURN GetCurrentWorkingDirectory(char* _dir, unsigned int _dirSize) override;

		GRETURN GetDirectorySize(unsigned int& _outSize) override;
		
		GRETURN GetFilesFromDirectory(char** _outFiles, unsigned int _numFiles, unsigned int _fileNameSize) override;

		GRETURN GetFileSize(const char* const _file, unsigned int& _outSize) override;

		GRETURN GetCount(unsigned int &_outCount) override;

		GRETURN IncrementCount() override;

		GRETURN DecrementCount() override;

		GRETURN RequestInterface(const GUUIID &_interfaceID, void** _outputInterface) override;
};

FileIO::FileIO() : m_refCount(1)
{
	m_currDir = nullptr;
}

FileIO::~FileIO()
{
	//Close the current directory
	closedir(m_currDir);

	//Close the file stream
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}
}

GRETURN FileIO::Init()
{
	//Set m_currDir to the directory the program was run from
	m_currDir = opendir(u8"./");
	if (!m_currDir)
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::OpenForBinaryRead(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//TODO: open the new file

	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenForBinaryWrite(const char* const _file, GFileOpenFlags _flags)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//TODO: open the new file

	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::OpenForTextRead(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//TODO: open the new file

	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenForTextWrite(const char* const _file, GFileOpenFlags _flags)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//TODO: open the new file
	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::Write(const char* const _inData, unsigned int _numBytes)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Write the bytes out
	m_file.write(_inData, _numBytes);

	return SUCCESS;
}

GRETURN FileIO::Read(char* _outData, unsigned int _numBytes)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Read the bytes in
	m_file.read(_outData, _numBytes);

	return SUCCESS;
}

GRETURN FileIO::WriteLine(const char* const _inData)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Write the line out
	m_file << _inData;

	return SUCCESS;
}

GRETURN FileIO::ReadLine(char* _outData, unsigned int _numBytes)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Read in data
	m_file.getline(_outData, _numBytes);

	return SUCCESS;
}

GRETURN FileIO::CloseFile()
{
	m_file.flush();
	m_file.close();

	return SUCCESS;
}

GRETURN FileIO::GetCurrentWorkingDirectory(char* _dir, unsigned int _dirSize)
{
	//TODO: Implement function

	return SUCCESS;
}

GRETURN FileIO::SetCurrentWorkingDirectory(const char* const _dir)
{
	//If there is an open directory, close it
	if (m_currDir != nullptr)
		closedir(m_currDir);

	//TODO: open new dir

	if (m_currDir == nullptr)
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::GetDirectorySize(unsigned int& _outSize)
{
	//Check that there is a current working directory
	if (m_currDir == nullptr)
		return FAILURE;

	//Ensure _outsize is initialized
	_outSize = 0;

	//Stores our files as we iterate through them
	struct dirent* file;
	while (file = readdir(m_currDir))
	{
		++_outSize;
	}

	//Set the directory iterater back to the begining
	rewinddir(m_currDir);

	return SUCCESS;
}

GRETURN FileIO::GetFilesFromDirectory(char** _outFiles, unsigned int _numFiles, unsigned int _fileNameSize)
{
	//Check that there is a current working directory
	if (m_currDir == nullptr)
		return FAILURE;

	//TODO: Implement function
	
	return SUCCESS;
}

GRETURN FileIO::GetFileSize(const char* const _file, unsigned int& _outSize)
{
	//TODO: implement this function

	return SUCCESS;
}

GRETURN FileIO::GetCount(unsigned int &_outCount)
{
	//TODO: implement function
	return SUCCESS;
}

GRETURN FileIO::IncrementCount()
{
	//TODO: implement function
	return SUCCESS;
}

GRETURN FileIO::DecrementCount()
{
	//TODO: implement function
	return SUCCESS;
}

GRETURN FileIO::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	if (_interfaceID == GFileUUIID)
	{
		GFile* convert = reinterpret_cast<GFile*>(this);
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

GRETURN GCreateFileHandler(GFile** _outFile)
{
	//Check that we were given a valid pointer
	if (_outFile == nullptr)
		return FAILURE;

	//Create the new object and make sure it's valid
	FileIO* file = new FileIO();
	if (!file)
		return FAILURE;

	GRETURN rv = file->Init();
	if (G_FAIL(rv))
		return rv;

	*_outFile = file;

	return SUCCESS;
}