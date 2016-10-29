/*!
	File: GFile.h
	Purpose: A Gateware interface that handles both binary and textual file io and directory
	Author: Justin W. Parks
	Contributors: N/A
	Last Modified: 10/26/2016
	Copyright: 7thGate Software LLC.
	License: MIT
*/

// GFile Inherits directly from GMultiThreaded 
#include "../G_Core/GMultiThreaded.h"

//! The core namespace to which all Gateware interfaces/structures/defines must belong
namespace GW
{
	enum GFileOpenFlags { APPEND, TRUNCATE };

	//! The core namespace to which all Gateware fundamental interfaces must belong
	namespace CORE
	{
		//! Unique Identifier for this interface. {3BE0F240-C3E7-424B-888E-F2994B6D1E48}
		static const GUUIID GFileUUIID =
		{
			0x3be0f240, 0xc3e7, 0x424b,{ 0x88, 0x8e, 0xf2, 0x99, 0x4b, 0x6d, 0x1e, 0x48 }
		};

		class GFile : public GMultiThreaded
		{
			// All Gateware API interfaces contain no variables & are pure virtual
		public:

			/** @brief Opens a file for binary read.
			*
			*  When using this function the file name should be passed assuming realitive
			*  pathing to the internally held directory. See SetCurrentWorkingDirectory and
			*  GetCurrentWorkingDirectory for more.
			*
			*  @param _file The file name of the file to open
			*  @return SUCCESS on successful open. Error code on failure
			*/
			virtual GRETURN OpenForBinaryRead(const char* const _file) = 0;

			/** @brief Opens a file for binary write.
			*
			*  When using this function the file name should be passed assuming realitive
			*  pathing to the internally held directory. See SetCurrentWorkingDirectory and
			*  GetCurrentWorkingDirectory for more.
			*
			*  @param _file The file name of the file to open
			*  @param _flags One or more GFileOpenFlags on how to open the file (TRUNCATE or APPEND)
			*  @return SUCCESS on successful open. Error code on failure
			*/
			virtual GRETURN OpenForBinaryWrite(const char* const _file, GFileOpenFlags _flags) = 0;

			/** @brief Opens a file for binary read.
			*
			*  When using this function the file name should be passed assuming realitive
			*  pathing to the internally held directory. See SetCurrentWorkingDirectory and
			*  GetCurrentWorkingDirectory for more.
			*
			*  @param _file The file name of the file to open
			*  @return SUCCESS on successful open. Error code on failure
			*/
			virtual GRETURN OpenForTextRead(const char* const _file) = 0;

			/** @brief Opens a file for binary write.
			*
			*  When using this function the file name should be passed assuming realitive
			*  pathing to the internally held directory. See SetCurrentWorkingDirectory and
			*  GetCurrentWorkingDirectory for more.
			*
			*  @param _file The file name of the file to open
			*  @param _flags One or more GFileOpenFlags on how to open the file (TRUNCATE or APPEND)
			*  @return SUCCESS on successful open. Error code on failure
			*/
			virtual GRETURN OpenForTextWrite(const char* const _file, GFileOpenFlags _flags) = 0;

			/** @brief Writes binary to the currently opened file.
			*
			*  @param _inData The data to write out to file
			*  @param _numBytes The number of bytes to write out to the file
			*  @return SUCCESS on successful write. Error code on failure
			*/
			virtual GRETURN Write(const char* const _inData, unsigned int _numBytes) = 0;

			/** @brief Reads binary from the currently opened file.
			*
			*  @param _outData The variable to store the read in bytes
			*  @param _numBytes The number of bytes to read in from the file
			*  @return SUCCESS on successful write. Error code on failure
			*/
			virtual GRETURN Read(char* _outData, unsigned int _numBytes) = 0;

			/** @brief Writes text to the currently opened file.
			*
			*  @param _inData The data to write out to file
			*  @return SUCCESS on successful write. Error code on failure
			*/
			virtual GRETURN WriteLine(const char* const _inData) = 0;

			/** @brief Reads text from the currently opened file.
			*
			*  @param _outData The variable to store the read in text
			*  @param _numBytes The size of _outData
			*  @return SUCCESS on successful read. Error code on failure
			*/
			virtual GRETURN ReadLine(char* _outData, unsigned int _numBytes) = 0;

			/** @brief Flushes and closes the current file
			*
			*  @return SUCCESS on successful close
			*/
			virtual GRETURN CloseFile() = 0;

			/** @brief Changes the current working directory
			*
			*  This is the directory where we will look for any file open commands.
			*
			*  @param _dir An absolute path to the directory to set as the current working directory
			*  @return SUCCESS on successful set. Error code on failure
			*/
			virtual GRETURN SetCurrentWorkingDirectory(const char* const _dir) = 0;
			//virtual GRETURN GetCurrentWorkingDirectory(char _dir[255]) = 0;

			/** @brief Gets the number of files in the current working directory
			*
			*  @param _outSize Stores the number of files in the directory
			*  @return SUCCESS on successful count. Error code on failure
			*/
			virtual GRETURN GetDirectorySize(unsigned int& _outSize) = 0;

			/** @brief Gets the names of all files in the current working directory
			*
			*  @param _outFiles Stores the names of the files retrieved
			*  @return SUCCESS on successful name retrieval. Error code on failure
			*/
			virtual GRETURN GetFilesFromDirectory(char** _outFiles) = 0;
		};

		/** @brief Creates a GFile Object
		*
		*  @param _outFile Stores the GFile object that has been created
		*  @return SUCCESS on successful creation. Error code on failure
		*/
		GRETURN GCreateFileHandler(GFile** _outFile);
	}
}