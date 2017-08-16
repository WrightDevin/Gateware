#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H
#endif
#include "../G_System/Common.h"
#include "G_Audio/GAudio.h"
#ifdef _WIN32
#include <xaudio2.h>
#include <xaudio2fx.h>
#elif __linux__
#include <time.h>
#include <pulse/mainloop.h>
#include <pulse/context.h>
#include <pulse/stream.h>
#include <pulse/error.h>
#include <pulse/scache.h>

#endif
const uint32_t fourRIFFcc = 'FFIR';
const uint32_t fourDATAcc = 'atad';
const uint32_t fourFMTcc = ' tmf';
const uint32_t fourWAVEcc = 'EVAW';
struct WAVE_FORMAT
{
	unsigned short myFormatTag;
	unsigned short myNumChannels;

	unsigned int nSamplesPerSec;
	unsigned int nAvgBytesPerSec;

	unsigned short nBlockAlign;

	unsigned short wBitsPerSample;
	unsigned short cbSize;
};
struct WAVE_DATA
{
	uint32_t byteSize; //  size of the buffer
	uint8_t * bytes; //represents audio data in bytes;
};
struct WAVE_FILE
{
	bool isSigned = true;
	WAVE_FORMAT format;
	WAVE_DATA data;
};

int LoadWav(const char * path, WAVE_FILE & returnedWave)
{
	
	int result = 0; //zero is good
	unsigned long dwChunktype = 0;
	unsigned long dwChunkDataSize = 0;
	unsigned long dwRiffDataSize = 0;
	unsigned long dwFileType = 0;
	unsigned long bytesRead = 0;
	unsigned long dwOffset = 0;
	unsigned long dwIsWave = 0;
	unsigned long throwAwayValue = 0;

	
	FILE * someWaveFile = NULL;
	someWaveFile = fopen(path, "r");

	if (someWaveFile != NULL)
	{
		while (result == 0)
		{
			unsigned long dwRead;
			dwRead = fread(&dwChunktype, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				//result = -1;
				break;
			}
			bytesRead += dwRead;

			dwRead = fread(&dwChunkDataSize, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				//result = -1;
				break;
			}
			bytesRead += dwRead;

			switch (dwChunktype)
			{
			case fourRIFFcc:
			{
				dwRiffDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;

				dwRead = fread(&dwFileType, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -1;
					break;
				}
				bytesRead += dwRead;
				break;
			}
			case fourWAVEcc:
			{

				dwRead = fread(&dwIsWave, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -1;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			case fourFMTcc:
			{
				dwRead = fread(&returnedWave.format, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -1;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			case fourDATAcc:
			{
				returnedWave.data.bytes = new uint8_t[dwChunkDataSize];
				dwRead = fread(returnedWave.data.bytes, 1, dwChunkDataSize, someWaveFile);

				returnedWave.data.byteSize = dwChunkDataSize;
				if (dwRead != dwChunkDataSize)
				{
					result = -1;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			default:
			{
				dwRead = fread(&throwAwayValue, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -1;
				}
				bytesRead += dwRead;
				break;
			}

			}

			dwOffset += 8;
			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRiffDataSize)
			{
				return -2;
			}
		}
		fclose(someWaveFile);
	}
	if (returnedWave.format.wBitsPerSample == 8)
	{
		returnedWave.isSigned = false;
	}
	else
	{
		returnedWave.isSigned = true;
	}
	return result;

}
HRESULT FindChunk(HANDLE & theFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	//by default code assumes its reading PCM file with 'RIFF', 'fmt ', and 'data' chunks
	//but in future I hope to include .mp3 if time allows


	//Check if file is valid
	HRESULT theResult = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	//Setting data variables
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;


	while (theResult == S_OK)
	{
		//populating variables with data from file

		DWORD dwRead;
		// reads in the chunk type 
		if (0 == ReadFile(theFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			theResult = HRESULT_FROM_WIN32(GetLastError());
		bytesRead += dwRead;

		if (0 == ReadFile(theFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			theResult = HRESULT_FROM_WIN32(GetLastError());
		bytesRead += dwRead;

		switch (dwChunkType)
		{
		case fourRIFFcc:
			// RIFF is header and contains info about the rest of the data

			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			dwChunkSize = 4;

			if (0 == ReadFile(theFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				theResult = HRESULT_FROM_WIN32(GetLastError());
			bytesRead += dwRead;

			break;

		default:
			//returns if it encounters a pointer error
			if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, dwChunkDataSize, NULL, FILE_CURRENT))
			{
				theResult = HRESULT_FROM_WIN32(GetLastError());
				return theResult;
			}
		}

		//updates the offset infromation to read from
		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc && dwChunkType)
		{
			//checks if this is the chunk we were looking for,
			//if so then returns
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize)
			return S_FALSE;
	}
	return theResult;
}
HRESULT ReadChunkData(HANDLE & theFile, void * someBuffer, DWORD buffersize, DWORD bufferOffset)
{
	HRESULT theResult = S_OK;
	//Checks if pointer is valid
	DWORD dResult = SetFilePointer(theFile, bufferOffset, NULL, FILE_BEGIN);
	if (dResult <= 0)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return theResult;
	}

	DWORD dwRead;
	//attempts to read data into the supplied buffer
	//If done successfully returns S_OK, otherwise returns error
	//theResult = myRead(theFile, someBuffer, buffersize, bufferOffset);
	BOOL theBool = ReadFile(theFile, someBuffer, buffersize, &dwRead, NULL);
	if (0 == (theBool))
		theResult = HRESULT_FROM_WIN32(GetLastError());

	return theResult;
}

int LoadWav(TCHAR * path, WAVEFORMATEXTENSIBLE & myWFX, XAUDIO2_BUFFER & myAudioBuffer)
{
	
	HRESULT theResult = S_OK;
	HANDLE theFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE == theFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkSize;
	DWORD dwChunkPosition;

	//checks the file type, expects a WAVE or XWMA
	//returns false otherwise
	theResult = FindChunk(theFile, fourRIFFcc, dwChunkSize, dwChunkPosition);
	if (theResult != S_OK)
	{
		return theResult;
	}
	DWORD filetype;

	theResult = ReadChunkData(theFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourWAVEcc)
		return S_FALSE;

	//finds and tries to load the FMT chunk, or file format info
	theResult = FindChunk(theFile, fourFMTcc, dwChunkSize, dwChunkPosition);
	if (theResult != S_OK)
	{
		return theResult;
	}
	theResult = ReadChunkData(theFile, &myWFX, dwChunkSize, dwChunkPosition);
	if (theResult != S_OK)
	{
		return theResult;
	}

	theResult = FindChunk(theFile, fourDATAcc, dwChunkSize, dwChunkPosition);
	if (theResult != S_OK)
	{
		return theResult;
	}
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	theResult = ReadChunkData(theFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	if (theResult != S_OK)
	{
		return theResult;
	}
	myAudioBuffer.AudioBytes = dwChunkSize; // this buffer contains all audio data
	myAudioBuffer.pAudioData = pDataBuffer; //contains size of the audio buffer in bytes
	myAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;// tells source this is EOF and should stop

	return theResult;
}
