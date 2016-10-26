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
			virtual GRETURN OpenForBinaryRead(const char* const _file) = 0;
			virtual GRETURN OpenForBinaryWrite(const char* const _file, GFileOpenFlags _flags) = 0;

			virtual GRETURN OpenForTextRead(const char* const _file) = 0;
			virtual GRETURN OpenForTextWrite(const char* const _file, GFileOpenFlags _flags) = 0;

			virtual GRETURN Write(const char* const _inData, unsigned int _numBytes) = 0;
			virtual GRETURN Read(char* _outData, unsigned int _numBytes) = 0;

			virtual GRETURN WriteLine(const char* const _inData) = 0;
			virtual GRETURN ReadLine(char* _outData, unsigned int _numBytes) = 0;

			virtual GRETURN CloseFile() = 0;

			virtual GRETURN SetCurrentWorkingDirectory(const char* const _dir) = 0;
			//virtual GRETURN GetCurrentWorkingDirectory(char _dir[255]) = 0;

			virtual GRETURN GetDirectorySize(unsigned int& _outSize) = 0;
			virtual GRETURN GetFilesFromDirectory(char** _outFiles) = 0;
		};

		GRETURN CreateFileHandler(GFile** _outFile);
	}
}