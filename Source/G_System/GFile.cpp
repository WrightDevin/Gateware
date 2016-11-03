#include "../../Interface/G_System/GFile.h"
#include <fstream>
#include <string>
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

#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>

#include "direntw.h"

#define DIR _WDIR
#define dirent _wdirent
#define fstream wfstream
#define string wstring

#define opendir _wopendir
#define readdir _wreaddir
#define closedir _wclosedir
#define rewinddir _wrewinddir 


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
	DIR* m_currDirStream;
	fstream m_file;
	string m_currDir;

	unsigned int m_dirSize;

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
	m_currDirStream = nullptr;
}

FileIO::~FileIO()
{
	//Close the current directory
	closedir(m_currDirStream);

	//Close the file stream
	if (m_file.is_open())
	{
		m_file.flush();
		m_file.close();
	}
}

GRETURN FileIO::Init()
{
	//Get the directory the program was ran in.
	//Because of the #defines this will run any of the three platforms we support.
	string currDirectory = G_TO_UTF16("./");
	
	//Open the directory the program was ran in.
	m_currDirStream = opendir(currDirectory.c_str());

	//Imbue the file with utf8 if on Windows
#if defined(_WIN32)

	std::locale utf8Locale(std::locale(), new std::codecvt_utf8<wchar_t>);
	m_file.imbue(utf8Locale);

#endif
	//If the directory is not open the the function fails
	if (m_currDirStream == nullptr)
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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::in | ios::binary);

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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::binary);

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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::binary | ios::app | ios::ate);

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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::in);

	if (!m_file.is_open())
		return FILE_NOT_FOUND;

	//Need to read the BOM if we are _WIN32
#if defined(_WIN32)
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	
	wchar_t BOM;
	m_file.get(BOM);

	_setmode(_fileno(stdout), oldMode);
#endif

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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out);

	if (!m_file.is_open())
		return FAILURE;

	//Need to write the BOM if we are _WIN32
#if defined(_WIN32)
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	
	m_file << L'\xFEFF';

	_setmode(_fileno(stdout), oldMode);
#endif

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
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::app | ios::ate);

	if (!m_file.is_open())
		return FAILURE;

	return SUCCESS;
}

GRETURN FileIO::Write(const char* const _inData, unsigned int _numBytes)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

#if defined(_WIN32)
	m_file.write((wchar_t*)_inData, _numBytes);

#elif define (__APPLE__) || defined(__linux__)
	m_file.write(_inData, _numBytes);

#endif

	return SUCCESS;
}

GRETURN FileIO::Read(char* _outData, unsigned int _numBytes)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Read the bytes in
#if defined(_WIN32)
	m_file.read((wchar_t*)_outData, _numBytes);

#elif defined (__APPLE__) || (__linux__)
	m_file.read(_outData, _numBytes);

#endif

	return SUCCESS;
}

GRETURN FileIO::WriteLine(const char* const _inData)
{
	//Ensure a file is open
	if (!m_file.is_open())
		return FAILURE;

	//Transfer the data to a string. #defines make it where
	//the string is what we need it to be on any system we support
	string writeOutString = G_TO_UTF16(_inData);

	//If _WIN32 we need to write out slightly different
#ifdef _WIN32
	int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
	
	m_file << writeOutString;

	_setmode(_fileno(stdout), oldMode);

#elif defined(__APPLE__) || defined(__linux__)

	m_file << writeOutString;

#endif 

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
	//Check to ensure there is a current working direcotry
	if (m_currDirStream == nullptr)
		return FAILURE;

	strcpy_s(_dir, _dirSize, G_TO_UTF8(m_currDir).c_str());

	return SUCCESS;
}

GRETURN FileIO::SetCurrentWorkingDirectory(const char* const _dir)
{
	//If there is an open directory, close it
	if (m_currDirStream != nullptr)
		closedir(m_currDirStream);

	//Open new directory
	string dirString = G_TO_UTF16(_dir);
	m_currDirStream = opendir(dirString.c_str());

	//Check to ensure directory is open
	if (m_currDirStream == nullptr)
		return FILE_NOT_FOUND;


	//Get the number of files in directory and the full path of the directory
	//Stores our files as we iterate through them
	struct dirent* file;
	while ((file = readdir(m_currDirStream)))
	{
		if(file->d_type == DT_REG)
			++m_dirSize;

		string currDir = G_TO_UTF16(".");
		if (file->d_name == currDir)
		{
			//TODO: Get fullpath
#if defined(_WIN32)
			TCHAR buffer[MAX_PATH];
			_wfullpath(buffer, file->d_name, MAX_PATH);

			m_currDir = buffer;
			m_currDir += L"\\";

#elif defined(__APPLE__)
#elif defined(__linux__)
			char* buffer[MAX_PATH];
			realpath(file->d_name, buffer);

			if (buffer == nullptr)
				return FILE_NOT_FOUND;

			m_currDir = buffer;
			m_currDir += "\";
#endif
		}
	}
	
	//Set the directory iterater back to the begining
	rewinddir(m_currDirStream);

	return SUCCESS;
}

GRETURN FileIO::GetDirectorySize(unsigned int& _outSize)
{
	//Check that there is a current working directory
	if (m_currDirStream == nullptr)
		return FAILURE;

	_outSize = m_dirSize;

	return SUCCESS;
}

GRETURN FileIO::GetFilesFromDirectory(char** _outFiles, unsigned int _numFiles, unsigned int _fileNameSize)
{
	//Check that there is a current working directory
	if (m_currDirStream == nullptr)
		return FAILURE;

	struct dirent* file;
	unsigned int fileNumber = 0;

	//Read the first file (Should be "." which will be skipped)
	file = readdir(m_currDirStream);
	if (file == nullptr)
		return FAILURE;

	//Read all files and add regular files to the buffer passed in
	for (; file != nullptr && fileNumber < _numFiles; file = readdir(m_currDirStream))
	{
		if (file->d_type == DT_REG)
		{
			strcpy_s(&(*_outFiles)[fileNumber], _fileNameSize, G_TO_UTF8(file->d_name).c_str());
			++fileNumber;
		}
	}

	return SUCCESS;
}

GRETURN FileIO::GetFileSize(const char* const _file, unsigned int& _outSize)
{
	//Make a full path to the file
	string filePath = m_currDir;
	filePath += G_TO_UTF16(_file);

#if defined (_WIN32)
	struct _stat s;
	if (_wstat(filePath.c_str(), &s) != 0)
		return FILE_NOT_FOUND;

#elif defined(__APPLE__) || defined(__linux__)
	struct stat s;
	if (stat(filePath.c_str(), &s) != 0)
		return FILE_NOT_FOUND;

#endif

	_outSize = s.st_size;

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

GRETURN CreateGFile(GFile** _outFile)
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
