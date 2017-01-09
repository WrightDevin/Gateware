#include "../../Interface/G_System/GFile.h"
#include <fstream>  //file streams
#include <string>  //strings
#include <atomic>  //automic variables
#include <mutex>  //mutex locks
#include "GUtility.h"  //Internal utility functions

//dirent.h is not native to Windows and is added to the project
//The " " are used for include so the compiler knows to look in the
//project folder first.
//dirent.h is native in Linux and Mac so the < > are used to include
#if defined(__APPLE__) || defined(__linux__)

//Apple and Linux includes
#include <dirent.h>  //Directory handling
#include <sys/stat.h>  //File stats

#define DIR_SEPERATOR '/'

#elif defined(_WIN32)

//Windows specific includes
#include <io.h>  //Included for mode change
#include <fcntl.h>  //Included for mode change
#include "direntw.h"

//Windows specific #defines
//This keeps most of the function's code branchless between platforms
#define DIR _WDIR
#define dirent _wdirent
#define fstream wfstream
#define string wstring

#define opendir _wopendir
#define readdir _wreaddir
#define closedir _wclosedir
#define rewinddir _wrewinddir

#define DIR_SEPERATOR L'\\'

#else

#error Gateware libraries are not currently supported for your platform

#endif

//The using statements for specifically what we are using
using namespace INTERNAL;
using std::string;
using std::fstream;
using std::ios;
using std::atomic;
using std::mutex;
using std::getline;

class FileIO : public GW::CORE::GFile
{
	DIR* m_currDirStream;  //Maintains the current directory
	fstream m_file;  //Maintains the current file (if one is open)
	
	string m_currDir;  //A cached directory path for faster fetching

	atomic<unsigned int> m_dirSize;  //A cached directory size for faster fetching

	atomic<unsigned int> m_refCount;  //Reference counter

	mutex m_lock; //Read/Write lock

public:
	FileIO();
	virtual ~FileIO();

	GW::GRETURN OpenBinaryRead(const char* const _file) override;

	GW::GRETURN OpenBinaryWrite(const char* const _file) override;

	GW::GRETURN AppendBinaryWrite(const char* const _file) override;

	GW::GRETURN OpenTextRead(const char* const _file) override;

	GW::GRETURN OpenTextWrite(const char* const _file) override;

	GW::GRETURN AppendTextWrite(const char* const _file) override;

	GW::GRETURN Write(const char* const _inData, unsigned int _numBytes) override;

	GW::GRETURN Read(char* _outData, unsigned int _numBytes) override;

	GW::GRETURN WriteLine(const char* const _inData) override;

	GW::GRETURN ReadLine(char* _outData, unsigned int _outDataSize, char _delimiter) override;

	GW::GRETURN CloseFile() override;

	GW::GRETURN FlushFile() override;

	GW::GRETURN SetCurrentWorkingDirectory(const char* const _dir) override;

	GW::GRETURN GetCurrentWorkingDirectory(char* _dir, unsigned int _dirSize) override;

	GW::GRETURN GetDirectorySize(unsigned int& _outSize) override;

	GW::GRETURN GetFilesFromDirectory(char* _outFiles[], unsigned int _numFiles, unsigned int _fileNameSize) override;

	GW::GRETURN GetFileSize(const char* const _file, unsigned int& _outSize) override;

	GW::GRETURN GetCount(unsigned int &_outCount) override;

	GW::GRETURN IncrementCount() override;

	GW::GRETURN DecrementCount() override;

	GW::GRETURN RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface) override;

	GW::GRETURN Init(); //The init function for this class in order to initialize variables
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

GW::GRETURN FileIO::Init()
{
	//Set the current working directory to the directory the program was ran from.
	GW::GRETURN rv = SetCurrentWorkingDirectory("./");
	if (G_FAIL(rv))
		return rv;

	//Imbue the file with utf8 if on Windows
#if defined(_WIN32)

	//Create a UTF8 Locale to imbue the fstream with
	std::locale utf8Locale(std::locale(), new std::codecvt_utf8<wchar_t>);

	//imbue the fstream
	m_file.imbue(utf8Locale);

#endif

	return GW::SUCCESS;
}

GW::GRETURN FileIO::OpenBinaryRead(const char* const _file)
{
	//Check for invalid arguments
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Ensure a file is not already open
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file in the currentWorkingDirectory
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::in | ios::binary);

	//If the file failed to open the function fails
	if (!m_file.is_open())
		return GW::FILE_NOT_FOUND;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::OpenBinaryWrite(const char* const _file)
{
	//Check for invalid arguments
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//If a file currently open we fail.
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::binary);

	//If file failed to open we fail
	if (!m_file.is_open())
		return GW::FAILURE;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::AppendBinaryWrite(const char* const _file)
{
	//Check for invalid arguments
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Close the current file if there is one
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::binary | ios::app | ios::ate);

	//If file failed to open we fail
	if (!m_file.is_open())
		return GW::FAILURE;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::OpenTextRead(const char* const _file)
{
	//Check for invalid arguments
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Close the current file if there is one
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::in);

	if (!m_file.is_open())
		return GW::FILE_NOT_FOUND;

#if defined(_WIN32)
	//If we are on windows we need to handle the file BOM.
	//This is what tells the system how to handle the file
	//This only needs to be read in one time so we will read it now
	//It can be ignored from this point on

	//Lock the read operation
	m_lock.lock();

	wchar_t BOM;
	m_file.get(BOM);

	m_lock.unlock();
#endif

	return GW::SUCCESS;
}

GW::GRETURN FileIO::OpenTextWrite(const char* const _file)
{
	//Check for invalid arguments
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Close the current file if there is one
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out);

	if (!m_file.is_open())
		return GW::FAILURE;

	//Need to write the BOM if we are _WIN32
#if defined(_WIN32)
	//If we are on windows we need to handle the file BOM.
	//This is what tells the system how to handle the file
	//This only needs to be wrote out one time so we will write it now
	//It can be ignored from this point on

	//Lock the write opertion
	m_lock.lock();

	m_file << L'\xFEFF'; //The imbue earlier will take this wide string and treat it as UTF8

	m_lock.unlock();
#endif

	return GW::SUCCESS;
}

GW::GRETURN FileIO::AppendTextWrite(const char* const _file)
{
	//Check for invalid arguements
	if (_file == nullptr)
		return GW::INVALID_ARGUMENT;

	//Close the current file if there is one
	if (m_file.is_open())
		return GW::FAILURE;

	//Open the new file
	m_file.open(m_currDir + G_TO_UTF16(_file), ios::out | ios::app | ios::ate);

	if (!m_file.is_open())
		return GW::FAILURE;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::Write(const char* const _inData, unsigned int _numBytes)
{
	//Check for invalid arguements
	if (_inData == nullptr || _numBytes == 0)
		return GW::INVALID_ARGUMENT;

	//Ensure a file is open
	if (!m_file.is_open())
		return GW::FAILURE;

	//Lock the write operations
	m_lock.lock();

	//On windows we need to cast the char* to a wchar_t*
	//We don't need to on MAC and Linux

#if defined(_WIN32)
	m_file.write((wchar_t*)_inData, _numBytes);

#elif defined(__APPLE__) || defined(__linux__)
	m_file.write(_inData, _numBytes);

#endif
	m_lock.unlock();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::Read(char* _outData, unsigned int _numBytes)
{
	if (_numBytes == 0)
		return GW::INVALID_ARGUMENT;

	//Ensure a file is open
	if (!m_file.is_open())
	{
		_outData = nullptr;
		return GW::FAILURE;
	}

	//Lock the read operations
	m_lock.lock();

	//On Windows we need to cast the char* to a wchar_t*
	//We don't need to on MAC or Linux
#if defined(_WIN32)
	m_file.read((wchar_t*)_outData, _numBytes);

#elif defined (__APPLE__) || (__linux__)
	m_file.read(_outData, _numBytes);

#endif
	m_lock.unlock();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::WriteLine(const char* const _inData)
{
	//Check for invalid arguements
	if (_inData == nullptr)
		return GW::INVALID_ARGUMENT;

	//Ensure a file is open
	if (!m_file.is_open())
		return GW::FAILURE;

	//Transfer the data to a string. #defines make it where
	//the string is what we need it to be on any system we support
	string writeOutString = G_TO_UTF16(_inData);

	//Lock the write operations
	m_lock.lock();

#ifdef _WIN32

	//Write out the string
	m_file << writeOutString;

#elif defined(__APPLE__) || defined(__linux__)

	//Write out the string
	m_file << writeOutString;

#endif

	m_lock.unlock();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::ReadLine(char* _outData, unsigned int _outDataSize, char _delimiter)
{
	if (_outData == nullptr || _outDataSize == 0)
		return GW::INVALID_ARGUMENT;

	//Ensure file is open
	if (!m_file.is_open())
		return GW::FAILURE;

	//The string to be read into
	string outString;

	//Lock the read operations
	m_lock.lock();

#ifdef _WIN32
	//Convert the UTF8 delimeter to UTF16
	const wchar_t* delimiter = G_TO_UTF16(_delimiter).c_str();

	//Read the information
	getline(m_file, outString, *delimiter);

#elif defined(__APPLE__) || defined(__linux__)

	//Just read in data normally
	getline(m_file, outString, _delimiter);
#endif

	//Copy the data over to the out parameter
	strcpy_s(_outData, _outDataSize, G_TO_UTF8(outString).c_str());

	m_lock.unlock();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::CloseFile()
{
	//If a file is not open, we can not close it
	if (!m_file.is_open())
		return GW::FAILURE;

	//Flush the file
	m_file.flush();

	//Close the file
	m_file.close();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::FlushFile()
{
	//If a file is not open we can not flush it
	if (!m_file.is_open())
		return GW::FAILURE;

	//flush the file
	m_file.flush();

	return GW::SUCCESS;
}

GW::GRETURN FileIO::GetCurrentWorkingDirectory(char* _dir, unsigned int _dirSize)
{
	//Check for valid arguements
	if (_dir == nullptr || _dirSize == 0)
		return GW::INVALID_ARGUMENT;

	//Check that a directory is open
	if (m_currDirStream == nullptr)
		return GW::FAILURE;

	//Copy the current directory to the out parameter
	strcpy_s(_dir, _dirSize, G_TO_UTF8(m_currDir).c_str());

	return GW::SUCCESS;
}

GW::GRETURN FileIO::SetCurrentWorkingDirectory(const char* const _dir)
{
	//Check for valid arguements
	if (_dir == nullptr)
		return GW::INVALID_ARGUMENT;

	//Get the absolute path
#if defined (_WIN32)
	wchar_t buffer[MAX_PATH];
	if (_wfullpath(buffer, G_TO_UTF16(_dir).c_str(), MAX_PATH) == nullptr)
		return GW::FAILURE;

	//Check to make sure the directory exists
	struct _stat s;
	if (_wstat(buffer, &s) != 0)
		return GW::FILE_NOT_FOUND;

#elif defined(__APPLE__) || defined(__linux__)
	//Get the absolute path
	char buffer[PATH_MAX];
	if (realpath(_dir, buffer) == nullptr)
		return GW::FAILURE;

	//Ensure the directory exists
	struct stat s;
	if (stat(buffer, &s) != 0)
		return GW::FILE_NOT_FOUND;
#endif

	//Assign the passed in directory to our internal directory storage.
	m_currDir = buffer;
	m_currDir += DIR_SEPERATOR;

	//If there is an open directory, close it
	if (m_currDirStream != nullptr)
		closedir(m_currDirStream);

	//Open new directory
	m_currDirStream = opendir(m_currDir.c_str());

	//Check to ensure directory is open
	if (m_currDirStream == nullptr)
		return GW::FAILURE;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::GetDirectorySize(unsigned int& _outSize)
{
	//Check that there is a current working directory
	if (m_currDirStream == nullptr)
		return GW::FAILURE;

	//Reset the dir size
	_outSize = 0;

	//Get the number of files in directory
	struct dirent* file;
	while ((file = readdir(m_currDirStream)))
	{
		if (file->d_type == DT_REG)
			++_outSize;
	}

	//Set the directory iterater back to the begining
	rewinddir(m_currDirStream);

	return GW::SUCCESS;
}

GW::GRETURN FileIO::GetFilesFromDirectory(char* _outFiles[], unsigned int _numFiles, unsigned int _fileNameSize)
{
	//Check that there is a current working directory
	if (m_currDirStream == nullptr)
		return GW::FAILURE;

	struct dirent* file;
	unsigned int fileNumber = 0;

	//Read the first file (Should be "." which will be skipped)
	file = readdir(m_currDirStream);
	if (file == nullptr)
		return GW::FAILURE;

	//Read all files and add regular files to the buffer passed in
	for (; file != nullptr && fileNumber < _numFiles; file = readdir(m_currDirStream))
	{
		if (file->d_type == DT_REG)
		{
            string fileName(file->d_name);
			strcpy_s(_outFiles[fileNumber], _fileNameSize, G_TO_UTF8(fileName).c_str());
			++fileNumber;
		}
	}

	return GW::SUCCESS;
}

GW::GRETURN FileIO::GetFileSize(const char* const _file, unsigned int& _outSize)
{
	//Make a full path to the file
	string filePath = m_currDir;
	filePath += G_TO_UTF16(_file);

	//Other then the UTF8 to UTF16 converstion for the windows calls
	//This is handled the same for each platform
	//wWe call stat() and it fills in the passed in function
	//with the stats of the passed in path
#if defined (_WIN32)
	struct _stat s;
	if (_wstat(filePath.c_str(), &s) != 0)
		return GW::FILE_NOT_FOUND;

#elif defined(__APPLE__) || defined(__linux__)
	struct stat s;
	if (stat(filePath.c_str(), &s) != 0)
		return GW::FILE_NOT_FOUND;

#endif

	//Copy the file size to the out parameter
	_outSize = (unsigned int)s.st_size;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::GetCount(unsigned int &_outCount)
{
	//Store ref count
	_outCount = m_refCount;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::IncrementCount()
{
	//Check to make sure overflow will not occur
	if (m_refCount == G_UINT_MAX)
		return GW::FAILURE;

	//Increment ref count
	++m_refCount;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::DecrementCount()
{
	//Check to make sure underflow will not occur
	if (m_refCount == 0)
		return GW::FAILURE;

	//Decrement ref count
	--m_refCount;

	return GW::SUCCESS;
}

GW::GRETURN FileIO::RequestInterface(const GW::GUUIID &_interfaceID, void** _outputInterface)
{
	if (_outputInterface == nullptr)
		return GW::INVALID_ARGUMENT;

	//If interface == this
	if (_interfaceID == GW::CORE::GFileUUIID)
	{
		//Temporary GFile* to ensure proper functions are called.
		GFile* convert = reinterpret_cast<GFile*>(this);

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

GW::GRETURN GW::CORE::GCreateFile(GFile** _outFile)
{
	//Check that we were given a valid pointer
	if (_outFile == nullptr)
		return GW::INVALID_ARGUMENT;

	//Create the new object and make sure it's valid
	FileIO* file = new FileIO();
	if (!file)
		return GW::FAILURE;

	//Run the FileIO init function
	GW::GRETURN rv = file->Init();
	if (G_FAIL(rv))
		return rv;

	//Store FileIO in the GFile
	*_outFile = file;

	return GW::SUCCESS;
}
