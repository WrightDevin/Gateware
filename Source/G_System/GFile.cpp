#include "../../Interface/G_System/GFile.h"
#include <fstream>
#include <string>
#include <string.h>
#include <atomic>
#include "GUtility.h"

//dirent.h is not native to Windows and is added to the project
//The " " are used for include so the compiler knows to look in the
//project folder first.
//dirent.h is native in Linux and Mac so the < > are used to include
#if defined(__APPLE__) || defined(__linux__)
#include <dirent.h>
#include <sys/stat.h>
#elif defined(_WIN32)
#include "direntw.h"
#else
#error Gateware libraries are not currently supported for your platform
#endif

#define G_UINT_MAX 0xffffffff

//The using statements for specifically what we are using
using namespace GW;
using namespace CORE;
using namespace INTERNAL;
using std::string;
using std::fstream;
using std::ios;
using std::atomic;

class FileIO : public GFile
{
	DIR* m_currDir;
	fstream m_file;

	atomic<unsigned int> m_refCount;

public:
	FileIO();
	~FileIO();

	GRETURN Init();

	GRETURN OpenBinaryRead(const char* const _file) override;

	GRETURN OpenBinaryWrite(const char* const _file) override;

	GRETURN AppendBinaryWrite(const char* const _file) override;

	GRETURN OpenTextRead(const char* const _file) override;

	GRETURN OpenTextWrite(const char* const _file) override;

	GRETURN AppendTextWrite(const char* const _file) override;

	GRETURN Write(const char* const _inData, unsigned int _numBytes) override;

	GRETURN Read(char* _outData, unsigned int _numBytes) override;

	GRETURN WriteLine(const char* const _inData) override;

	GRETURN ReadLine(char* _outData, unsigned int _numBytes) override;

	GRETURN CloseFile() override;

	GRETURN FlushFile() override;

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

GRETURN FileIO::OpenBinaryRead(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::in | ios::binary);

	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenBinaryWrite(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::out | ios::binary);

	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::AppendBinaryWrite(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::out | ios::binary | ios::app | ios::ate);

	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::OpenTextRead(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::in);

	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	return SUCCESS;
}

GRETURN FileIO::OpenTextWrite(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::out);

	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::AppendTextWrite(const char* const _file)
{
	//Close the current file if there is one
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}

	//Open the new file
	m_file.open(G_WIDEN(_file), ios::out | ios::app | ios::ate);

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
	if (!m_file.is_open())
		return FAILURE;

	m_file.flush();
	m_file.close();

	return SUCCESS;
}

GRETURN FileIO::FlushFile()
{
	if (!m_file.is_open())
		return FAILURE;

	m_file.flush();

	return SUCCESS;
}

GRETURN FileIO::GetCurrentWorkingDirectory(char* _dir, unsigned int _dirSize)
{
	if (m_currDir == nullptr)
		return FAILURE;

	//Iterate to find current directory. This should be the first thing found.
	struct dirent* file = nullptr;
	while ((file = readdir(m_currDir)) != nullptr)
	{
        string currDir = ".";
		if (file->d_name == currDir)
		{
			//TODO: Implement platform specific get full path (DO THIS ON SETTING CURRENT DIRECTORY AND STORE IN CLASS)
		}
	}

	//Rewind the directory back to begining
	rewinddir(m_currDir);

	return FAILURE;
}

GRETURN FileIO::SetCurrentWorkingDirectory(const char* const _dir)
{
	//If there is an open directory, close it
	if (m_currDir != nullptr)
		closedir(m_currDir);

	//Open the new directory
	m_currDir = opendir(_dir);

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
	while ((file = readdir(m_currDir)))
	{
		if(file->d_type == DT_REG)
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

	struct dirent* file;
	unsigned int fileNumber = 0;

	//Read the first file (Should be "." which will be skipped)
	file = readdir(m_currDir);
	if (file == nullptr)
		return FAILURE;

	//Read all files and add regular files to the buffer passed in
	for (; file != nullptr && fileNumber < _numFiles; file = readdir(m_currDir))
	{
		if (file->d_type == DT_REG)
		{
            strlcpy_s(&(*_outFiles)[fileNumber], _fileNameSize, file->d_name);
			++fileNumber;
		}
	}

	return SUCCESS;
}

GRETURN FileIO::GetFileSize(const char* const _file, unsigned int& _outSize)
{
	//TODO: Make function widebyte
	struct stat s;
	//_wstat(_file, &s);


	return SUCCESS;
}

GRETURN FileIO::GetCount(unsigned int &_outCount)
{
	//Store ref count
	_outCount = m_refCount;

	return SUCCESS;
}

GRETURN FileIO::IncrementCount()
{
	//Check to make sure overflow will not occur
	if (m_refCount == G_UINT_MAX)
		return FAILURE;

	//Increment ref count
	++m_refCount;

	return SUCCESS;
}

GRETURN FileIO::DecrementCount()
{
	//Check to make sure underflow will not occur
	if (m_refCount == 0)
		return FAILURE;

	//Decrement ref count
	--m_refCount;

	return SUCCESS;
}

GRETURN FileIO::RequestInterface(const GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return INVALID_ARGUMENT;

	//If interface == this
	if (_interfaceID == GFileUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GFile* convert = reinterpret_cast<GFile*>(this);

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

GRETURN GCreateFileHandler(GFile** _outFile)
{
	//Check that we were given a valid pointer
	if (_outFile == nullptr)
		return INVALID_ARGUMENT;

	//Create the new object and make sure it's valid
	FileIO* file = new FileIO();
	if (!file)
		return FAILURE;

	//Run the FileIO init function
	GRETURN rv = file->Init();
	if (G_FAIL(rv))
		return rv;

	//Store FileIO in the GFile
	*_outFile = file;

	return SUCCESS;
}
