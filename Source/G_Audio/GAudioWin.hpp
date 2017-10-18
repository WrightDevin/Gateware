// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <vector>
#include <iostream>
#include <thread>

using namespace GW;
using namespace AUDIO;

const unsigned long fourRIFFcc = 'FFIR';
const unsigned long fourDATAcc = 'atad';
const unsigned long fourFMTcc = ' tmf';
const unsigned long fourWAVEcc = 'EVAW';
const unsigned long fourXWMAcc = 'AMWX';
const unsigned long fourDPDScc = 'sdpd';

#define STREAMING_BUFFER_SIZE 65536
#define MAX_BUFFER_COUNT 3
HRESULT LoadWaveData(const char * path, WAVEFORMATEXTENSIBLE & myWFX, XAUDIO2_BUFFER & myAudioBuffer)
{
	//WAVEFORMATEXTENSIBLE myWFX = { 0 };
	//XAUDIO2_BUFFER myAudioBuffer = { 0 };
	HRESULT theResult = S_OK;

	wchar_t* tpath = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, path, -1, tpath, 4096);
	//if can't find file for unit tests, use : _wgetcwd to see where to put test file 
	HANDLE theFile = CreateFile(tpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE == theFile)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());


	int result = 0; //zero is good
	unsigned long dwChunktype = 0;
	unsigned long dwChunkDataSize = 0;
	unsigned long dwRiffDataSize = 0;
	unsigned long dwFileType = 0;
	unsigned long bytesRead = 0;

	unsigned long dwIsWave = 0;
	unsigned long throwAwayValue = 0;
	bool foundAudioData = false;
	while (result == 0)
	{
		unsigned long dwRead;
		ReadFile(theFile, &dwChunktype, 4, &dwRead, NULL);
		if (dwRead != 4)
		{
			result = -1;
			break;
		}
		bytesRead += dwRead;
		ReadFile(theFile, &dwChunkDataSize, 4, &dwRead, NULL);
		if (dwRead != 4)
		{
			result = -2;
			break;
		}
		bytesRead += dwRead;

		switch (dwChunktype)
		{
		case fourRIFFcc:
		{
			dwRiffDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			ReadFile(theFile, &dwFileType, 4, &dwRead, NULL);
			if (dwRead != 4)
			{
				result = -3;
				break;
			}
			if (dwFileType != fourWAVEcc)
			{
				result = -3;
				break;
			}
			bytesRead += dwRead;
			break;
		}
		case fourWAVEcc:
		{
			ReadFile(theFile, &dwIsWave, 4, &dwRead, NULL);
			if (dwRead != 4)
			{
				result = -4;
				break;
			}
			bytesRead += dwRead;

			break;
		}
		case fourFMTcc:
		{
			ReadFile(theFile, &myWFX, dwChunkDataSize, &dwRead, NULL);
			if (dwRead != dwChunkDataSize)
			{
				result = -5;
				break;
			}
			bytesRead += dwRead;

			break;
		}
		case fourDATAcc:
		{
			BYTE * pDataBuffer = new BYTE[dwChunkDataSize];
			ReadFile(theFile, pDataBuffer, dwChunkDataSize, &dwRead, NULL);

			if (dwRead != dwChunkDataSize)
			{
				result = -6;
				break;
			}
			myAudioBuffer.AudioBytes = dwChunkDataSize;  //contains size of the audio buffer in bytes
			myAudioBuffer.pAudioData = pDataBuffer;  // this buffer contains all audio data
			myAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;// tells source this is EOF and should stop
			bytesRead += dwRead;
			foundAudioData = true;
			break;
		}
		default:
		{
			ReadFile(theFile, &throwAwayValue, dwChunkDataSize, &dwRead, NULL);
			if (dwRead != dwChunkDataSize)
			{
				result = -7;
			}
			bytesRead += dwRead;
			break;
		}

		}



		if (bytesRead - 8 >= dwRiffDataSize)//excludes the first 8 byte header information
		{

			break;
		}
	}
	if (result < 0)
	{
		theResult = S_FALSE;
		return theResult;
	}


	return theResult;
}
HRESULT LoadOnlyWaveHeaderData(const char * path, HANDLE & returnedHandle, WAVEFORMATEXTENSIBLE & myWFX, XAUDIO2_BUFFER & myAudioBuffer, DWORD & dataSize)
{

	HRESULT theResult = S_OK;

	wchar_t* tpath = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, path, -1, tpath, 4096);
	//if can't find file for unit tests, use : _wgetcwd to see where to put test file 

	returnedHandle = CreateFile(tpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (INVALID_HANDLE_VALUE == returnedHandle)
		return HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(returnedHandle, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());


	int result = 0; //zero is good
	unsigned long dwChunktype = 0;
	unsigned long dwChunkDataSize = 0;
	unsigned long dwRiffDataSize = 0;
	unsigned long dwFileType = 0;
	unsigned long bytesRead = 0;

	unsigned long dwIsWave = 0;
	unsigned long throwAwayValue = 0;
	bool foundAudioData = false;
	while (result == 0)
	{
		unsigned long dwRead;
		ReadFile(returnedHandle, &dwChunktype, 4, &dwRead, NULL);
		if (dwRead != 4)
		{
			result = -1;
			break;
		}
		bytesRead += dwRead;
		ReadFile(returnedHandle, &dwChunkDataSize, 4, &dwRead, NULL);
		if (dwRead != 4)
		{
			result = -2;
			break;
		}
		bytesRead += dwRead;

		switch (dwChunktype)
		{
		case fourRIFFcc:
		{
			dataSize = dwRiffDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			ReadFile(returnedHandle, &dwFileType, 4, &dwRead, NULL);
			if (dwRead != 4)
			{
				result = -3;
				break;
			}
			if (dwFileType != fourWAVEcc)
			{
				result = -3;
				break;
			}
			bytesRead += dwRead;
			break;
		}
		case fourWAVEcc:
		{
			ReadFile(returnedHandle, &dwIsWave, 4, &dwRead, NULL);
			if (dwRead != 4)
			{
				result = -4;
				break;
			}
			bytesRead += dwRead;

			break;
		}
		case fourFMTcc:
		{
			ReadFile(returnedHandle, &myWFX, dwChunkDataSize, &dwRead, NULL);
			if (dwRead != dwChunkDataSize)
			{
				result = -5;
				break;
			}
			bytesRead += dwRead;
			result = 1; //break us out of loop
			break;
		}


		}


	}
	if (result < 0)
	{
		theResult = S_FALSE;
		return theResult;
	}


	return theResult;
}

HRESULT LoadWaveData2(const char * path, WAVEFORMATEXTENSIBLE & myWFX, XAUDIO2_BUFFER & myAudioBuffer)
{
	//WAVEFORMATEXTENSIBLE myWFX = { 0 };
	//XAUDIO2_BUFFER myAudioBuffer = { 0 };
	HRESULT theResult = S_OK;

	//wchar_t* tpath = new wchar_t[4096];
	//MultiByteToWideChar(CP_ACP, 0, path, -1, tpath, 4096);
	//if can't find file for unit tests, use : _wgetcwd to see where to put test file 
	//HANDLE theFile = CreateFile(tpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//if (INVALID_HANDLE_VALUE == theFile)
		//return HRESULT_FROM_WIN32(GetLastError());

	//if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, 0, NULL, FILE_BEGIN))
		//return HRESULT_FROM_WIN32(GetLastError());


	int result = 0; //zero is good
	unsigned long dwChunktype = 0;
	unsigned long dwChunkDataSize = 0;
	unsigned long dwRiffDataSize = 0;
	unsigned long dwFileType = 0;
	unsigned long bytesRead = 0;

	unsigned long dwIsWave = 0;
	unsigned long throwAwayValue = 0;
	bool foundAudioData = false;
	FILE * someWaveFile = NULL;
	someWaveFile = fopen(path, "r");
	if (someWaveFile == NULL)
	{
		return 1;
	}
	if (someWaveFile != NULL)
	{
		while (result == 0)
		{
			unsigned long dwRead;
			//ReadFile(theFile, &dwChunktype, 4, &dwRead, NULL);
			dwRead = fread(&dwChunktype, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				result = -1;
				break;
			}
			bytesRead += dwRead;
			//ReadFile(theFile, &dwChunkDataSize, 4, &dwRead, NULL);
			dwRead = fread(&dwChunkDataSize, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				result = -2;
				break;
			}
			bytesRead += dwRead;

			switch (dwChunktype)
			{
			case fourRIFFcc:
			{
				dwRiffDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				//ReadFile(theFile, &dwFileType, 4, &dwRead, NULL);
				dwRead = fread(&dwFileType, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -3;
					break;
				}
				if (dwFileType != fourWAVEcc)
				{
					result = -3;
					break;
				}
				bytesRead += dwRead;
				break;
			}
			case fourWAVEcc:
			{
				//ReadFile(theFile, &dwIsWave, 4, &dwRead, NULL);
				dwRead = fread(&dwIsWave, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -4;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			case fourFMTcc:
			{
				//ReadFile(theFile, &myWFX, dwChunkDataSize, &dwRead, NULL);
				dwRead = fread(&myWFX, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -5;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			case fourDATAcc:
			{
				BYTE * pDataBuffer = new BYTE[dwChunkDataSize];
				//ReadFile(theFile, pDataBuffer, dwChunkDataSize, &dwRead, NULL);
				dwRead = fread(pDataBuffer, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -6;
					break;
				}
				myAudioBuffer.AudioBytes = dwChunkDataSize;  //contains size of the audio buffer in bytes
				myAudioBuffer.pAudioData = pDataBuffer;  // this buffer contains all audio data
				myAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;// tells source this is EOF and should stop
				bytesRead += dwRead;
				foundAudioData = true;
				break;
			}
			default:
			{
				//ReadFile(theFile, &throwAwayValue, dwChunkDataSize, &dwRead, NULL);
				dwRead = fread(&throwAwayValue, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -7;
				}
				bytesRead += dwRead;
				break;
			}

			}



			if (bytesRead - 8 >= dwRiffDataSize)//excludes the first 8 byte header information
			{

				break;
			}
		}
		if (result < 0)
		{
			theResult = S_FALSE;
			return theResult;
		}
	}

	return theResult;
}
HRESULT LoadOnlyWaveHeaderData2(const char * path, WAVEFORMATEXTENSIBLE & myWFX, XAUDIO2_BUFFER & myAudioBuffer, DWORD & dataSize)
{

	HRESULT theResult = S_OK;

	//wchar_t* tpath = new wchar_t[4096];
	//MultiByteToWideChar(CP_ACP, 0, path, -1, tpath, 4096);
	//if can't find file for unit tests, use : _wgetcwd to see where to put test file 

	//returnedHandle = CreateFile(tpath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//if (INVALID_HANDLE_VALUE == returnedHandle)
		//return HRESULT_FROM_WIN32(GetLastError());

	//if (INVALID_SET_FILE_POINTER == SetFilePointer(returnedHandle, 0, NULL, FILE_BEGIN))
		//return HRESULT_FROM_WIN32(GetLastError());


	int result = 0; //zero is good
	unsigned long dwChunktype = 0;
	unsigned long dwChunkDataSize = 0;
	unsigned long dwRiffDataSize = 0;
	unsigned long dwFileType = 0;
	unsigned long bytesRead = 0;

	unsigned long dwIsWave = 0;
	unsigned long throwAwayValue = 0;
	bool foundAudioData = false;
	FILE * someWaveFile = NULL;
	someWaveFile = fopen(path, "r");
	if (someWaveFile == NULL)
	{
		return 1;
	}
	if (someWaveFile != NULL)
	{
		while (result == 0)
		{
			unsigned long dwRead;
			//ReadFile(theFile, &dwChunktype, 4, &dwRead, NULL);
			dwRead = fread(&dwChunktype, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				result = -1;
				break;
			}
			bytesRead += dwRead;
			//ReadFile(theFile, &dwChunkDataSize, 4, &dwRead, NULL);
			dwRead = fread(&dwChunkDataSize, 1, 4, someWaveFile);
			if (dwRead != 4)
			{
				result = -2;
				break;
			}
			bytesRead += dwRead;

			switch (dwChunktype)
			{
			case fourRIFFcc:
			{
				dwRiffDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				//ReadFile(theFile, &dwFileType, 4, &dwRead, NULL);
				dwRead = fread(&dwFileType, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -3;
					break;
				}
				if (dwFileType != fourWAVEcc)
				{
					result = -3;
					break;
				}
				bytesRead += dwRead;
				break;
			}
			case fourWAVEcc:
			{
				//ReadFile(theFile, &dwIsWave, 4, &dwRead, NULL);
				dwRead = fread(&dwIsWave, 1, 4, someWaveFile);
				if (dwRead != 4)
				{
					result = -4;
					break;
				}
				bytesRead += dwRead;

				break;
			}
			case fourFMTcc:
			{
				//ReadFile(theFile, &myWFX, dwChunkDataSize, &dwRead, NULL);
				dwRead = fread(&myWFX, 1, dwChunkDataSize, someWaveFile);
				if (dwRead != dwChunkDataSize)
				{
					result = -5;
					break;
				}
				bytesRead += dwRead;
				result = 1; //break us out of loop
				break;
			}

			}
			if (result < 0)
			{
				theResult = S_FALSE;
				return theResult;
			}
		}


		if (result < 0)
		{
			theResult = S_FALSE;
		}
	}

	return theResult;
}


HRESULT FindChunk(HANDLE & theFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition, DWORD & dwRiffSize)
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

			dwRiffSize = dwRIFFDataSize;

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

struct StreamingVoiceContext : public IXAudio2VoiceCallback
{
	HANDLE hBufferEndEvent;
	HANDLE hStreamEndEvent;
	//StreamingVoiceContext() : hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)) {}
	StreamingVoiceContext() :
#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
	hBufferEndEvent(CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE)), hStreamEndEvent(CreateEventEx(nullptr, nullptr, CREATE_EVENT_MANUAL_RESET, EVENT_MODIFY_STATE | SYNCHRONIZE)){}
#else
		hBufferEndEvent(CreateEvent(nullptr, FALSE, FALSE, nullptr)), hStreamEndEvent(CreateEvent(nullptr, FALSE, FALSE, nullptr)) {}
#endif	
	virtual ~StreamingVoiceContext() { CloseHandle(hBufferEndEvent); CloseHandle(hStreamEndEvent); }
	void OnBufferEnd(void*) { SetEvent(hBufferEndEvent); }
	void OnVoiceProcessingPassStart(UINT32) {  }
	void OnVoiceProcessingPassEnd() {  }
	void OnVoiceError(void*, HRESULT) {  }
	void OnStreamEnd() { SetEvent(hStreamEndEvent); }
	void OnBufferStart(void*) {  }
	void OnLoopEnd(void*) {  }
	void OnLoopEnd(void*, HRESULT) {  }


};
class WindowAppAudio;
class WindowAppSound : public GSound
{
public:
	int index = -1;
	WindowAppAudio * audio;
	IXAudio2SourceVoice * mySourceVoice = nullptr;
	IXAudio2SubmixVoice * mySubmixVoice = nullptr;
	WAVEFORMATEX myWFM = {0};
	XAUDIO2_BUFFER myAudioBuffer = { 0 };
	bool loops = false;
	bool isPlaying = false;
	bool isPaused = false;
	float volume = 1.0f;
	GReturn Init();
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn CheckChannelVolumes(const float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn GetChannels(uint32_t & returnedChannelNum );
	GReturn Play();
	GReturn Pause();
	GReturn Resume();
	GReturn StopSound();
	~WindowAppSound();
};

class WindowAppMusic : public GMusic
{
private:
	BYTE buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];
	OVERLAPPED overlap = { 0 };
public:
	char *  myFile;
	int index = -1;
	DWORD dataSize;
	WindowAppAudio * audio;
	IXAudio2SourceVoice * mySourceVoice = nullptr;
	IXAudio2SubmixVoice * mySubmixVoice = nullptr;
	WAVEFORMATEX myWFM = {0};
	std::thread* streamThread = nullptr;
	XAUDIO2_BUFFER myAudioBuffer = { 0 };

	bool loops = false;
	bool isPlaying = false;
	bool isPaused = false;
	bool stopFlag = false;
	float volume = 1.0f;
	GReturn Init();
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn CheckChannelVolumes(const float *_values, int _numChannels);
	GReturn GetChannels(uint32_t & returnedChannelNum);
	GReturn SetVolume(float _newVolume);
	GReturn StreamStart();
	GReturn Stream();
	GReturn PauseStream();
	GReturn ResumeStream();
	GReturn StopStream();
	~WindowAppMusic();


	StreamingVoiceContext myContext;
};


class WindowAppAudio : public GAudio
{
public:
	std::vector<WindowAppSound *> activeSounds;
	std::vector<WindowAppMusic *> activeMusic;
	IXAudio2 * myAudio = nullptr;
	float maxVolume;
	int maxChannels;
	int numberOfOutputs = 2;
	IXAudio2MasteringVoice * theMasterVoice = nullptr;
	GReturn Init(int _numOfOutputs = 2);
	GReturn CreateSound(const char* _path, GSound** _outSound);
	GReturn CreateMusicStream(const char* _path, GMusic** _outMusic);
	GReturn SetMasterVolume(float _value);
	GReturn SetMasterChannelVolumes(const float * _values, int _numChannels);
	GReturn PauseAll();
	GReturn ResumeAll();
	GReturn StopAll();
	~WindowAppAudio();

};
//Start of GSound implementation 
GReturn WindowAppSound::Init()
{
	GReturn result = GReturn::FAILURE;
	HRESULT theResult = S_OK;
	if (FAILED(theResult = mySourceVoice->SubmitSourceBuffer(&myAudioBuffer)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return result;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::SetPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	return result;
}
GReturn WindowAppSound::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	if (_values == nullptr)
		return result;
	result = FAILURE;
	for (int i = 0; i < _numChannels; i++)
	{
		try
		{
			if (_values[i] > audio->maxVolume)
			{
				_values[i] = audio->maxVolume;
			}
		}
		catch (const std::exception& e)
		{
			return result;
		}

	}
	unsigned int sourceChannels = 0;
	GetChannels(sourceChannels);
	HRESULT theResult = S_OK;


	// can only support up to 6 outputs
	int matrixSize = sourceChannels * audio->numberOfOutputs;
	float * matrix = new float[matrixSize];

	for (size_t i = 0; i < matrixSize; i++)
	{
		if (i < _numChannels)
		{
			matrix[i] = _values[i];
		}
		else
		{
			matrix[i] = 0;
		}
	}
	if (FAILED(theResult = mySourceVoice->SetOutputMatrix(mySubmixVoice, sourceChannels, audio->numberOfOutputs, matrix)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		delete matrix;
		return result;
	}
	delete matrix;

	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;
	if (_numChannels <= 0)
		return result;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	if (_values == nullptr)
		return result;

	uint32_t currentChannels;
	result = GetChannels(currentChannels);
	if (result != SUCCESS)
		return result;
	float * currentValues = (float *)malloc(currentChannels);
	
	mySourceVoice->GetChannelVolumes(_numChannels, currentValues);
	if (currentValues == nullptr)
		return result;

	bool didChange = false;
	for (int i = 0; i < _numChannels; i++)
	{
		try
		{
			if (currentValues[i] > _values[i])
			{
				currentValues[i] = _values[i];
				didChange = true;
			}
		}
		catch (const std::exception& e)
		{
			return result;
		}

	}
	HRESULT theResult = S_OK;
	if (didChange == true)
	{
		if (FAILED(theResult = mySourceVoice->SetChannelVolumes(_numChannels, _values)))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::GetChannels(uint32_t & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == NULL)
	{
		return result;
	}
	returnedChannelNum = myWFM.nChannels;
	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::SetVolume(float _newVolume)
{
	GReturn result = INVALID_ARGUMENT;
	if (_newVolume < 0.0f)
		return result;
	result = SUCCESS;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;


	if (_newVolume > audio->maxVolume)
	{
		_newVolume = audio->maxVolume;
	}
	HRESULT theResult = S_OK;
	if (FAILED(theResult = mySourceVoice->SetVolume(_newVolume)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return result;
	}
	result = SUCCESS;

	return result;
}
GReturn WindowAppSound::Play()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (isPlaying)
	{
		result = StopSound();
		if (result != SUCCESS)
			return result;
	}
	if (!isPlaying)
	{
		if (FAILED(theResult = mySourceVoice->Start()))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = true;
		isPaused = false;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::Pause()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (!isPaused)
	{
		if (FAILED(theResult = mySourceVoice->Stop()))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = false;
		isPaused = true;
	}
	result = SUCCESS;
	return result;

}
GReturn WindowAppSound::Resume()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (!isPlaying)
	{
		if (FAILED(theResult = mySourceVoice->Start()))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = true;
		isPaused = false;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::StopSound()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;

	if (FAILED(theResult = mySourceVoice->Stop()))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return result;
	}
	mySourceVoice->FlushSourceBuffers();

	if (FAILED(theResult = mySourceVoice->SubmitSourceBuffer(&myAudioBuffer)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return result;
	}
	isPlaying = false;
	isPaused = true;

	result = SUCCESS;
	return result;
}
WindowAppSound::~WindowAppSound()
{


}
//End of GSound implementation

//Start of GMusic implementation
GReturn WindowAppMusic::Init()
{
	GReturn result = GReturn::FAILURE;
	overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::SetPCMShader(const char* _data)
{
	GReturn result = FAILURE;

	return result;
}
GReturn WindowAppMusic::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	if (_values == nullptr)
		return result;
	result = FAILURE;
	for (int i = 0; i < _numChannels; i++)
	{
		try
		{
			if (_values[i] > audio->maxVolume)
			{
				_values[i] = audio->maxVolume;
			}
		}
		catch (const std::exception& e)
		{
			return result;
		}

	}
	unsigned int sourceChannels = 0;
	GetChannels(sourceChannels);
	HRESULT theResult = S_OK;


	// can only support up to 6 outputs
	int matrixSize = sourceChannels * audio->numberOfOutputs;
	float * matrix = new float[matrixSize];
	
	for (size_t i = 0; i < matrixSize; i++)
	{
		if (i < _numChannels)
		{
			matrix[i] = _values[i];
		}
		else
		{
			matrix[i] = 0;
		}
	}
	if (FAILED(theResult = mySourceVoice->SetOutputMatrix(mySubmixVoice, sourceChannels, audio->numberOfOutputs, matrix)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		delete matrix;
		return result;
	}
	delete matrix;

	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	if (_values == nullptr)
		return result;

	result = FAILURE;
	uint32_t currentChannels;
	result = GetChannels(currentChannels);
	if (result != SUCCESS)
		return result;
	float * currentValues = (float *)malloc(currentChannels);

	mySourceVoice->GetChannelVolumes(_numChannels, currentValues);

	if (currentValues == nullptr)
		return result;

	bool didChange = false;
	for (int i = 0; i < _numChannels; i++)
	{
		try
		{
			if (currentValues[i] > _values[i])
			{
				currentValues[i] = _values[i];
				didChange = true;
			}
		}
		catch (const std::exception& e)
		{
			return result;
		}

	}
	HRESULT theResult = S_OK;
	if (didChange == true)
	{
		if (FAILED(theResult = mySourceVoice->SetChannelVolumes(_numChannels, _values)))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::GetChannels(uint32_t & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == NULL)
	{
		return result;
	}
	result = INVALID_ARGUMENT;
	
	returnedChannelNum = myWFM.nChannels;
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::SetVolume(float _newVolume)
{
	GReturn result = FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	result = INVALID_ARGUMENT;
	if (_newVolume < 0.0f)
		return result;
	result = FAILURE;
	if (_newVolume > audio->maxVolume)
	{
		_newVolume = audio->maxVolume;
	}
	HRESULT theResult = S_OK;
	if (FAILED(theResult = mySourceVoice->SetVolume(_newVolume)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return result;
	}
	result = SUCCESS;

	return result;
}
GReturn WindowAppMusic::Stream()
{
	HRESULT theResult = S_OK;
	HANDLE theFile = myFile;


	if (INVALID_HANDLE_VALUE == theFile)
		theResult = HRESULT_FROM_WIN32(GetLastError());

	DWORD ptrLocation = 0;
	if (INVALID_SET_FILE_POINTER == (ptrLocation = SetFilePointer(theFile, 0, NULL, FILE_BEGIN)))
		theResult = HRESULT_FROM_WIN32(GetLastError());
	myAudioBuffer.Flags = 0;
	XAUDIO2_VOICE_STATE state;
	mySourceVoice->GetState(&state);
	XAUDIO2_SEND_DESCRIPTOR send = { 0, mySourceVoice };
	XAUDIO2_VOICE_SENDS sendlist = { 1, &send };
	send.pOutputVoice = mySubmixVoice;
	mySubmixVoice->SetOutputVoices(&sendlist);

	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dataSize = 0;
	//checks the file type, expects a WAVE or XWMA
	//returns false otherwise
	theResult = FindChunk(theFile, fourRIFFcc, dwChunkSize, dwChunkPosition, dataSize);
	if (theResult != S_OK)
	{
		return FAILURE;
	}

	int CurrentDiskReadBuffer = 0;
	int CurrentPosition = 0;
	int cbWaveSize = dataSize;
	//uint8_t * byteBuffer = new uint8_t[STREAMING_BUFFER_SIZE];
	int dwDataSize = dataSize;
	while (CurrentPosition < cbWaveSize && stopFlag == false)
	{
	
		if (!isPaused)
		{
			DWORD dwRead;
			//if (SUCCEEDED(theResult) && 0 == ReadFile(theFile, &byteBuffer, dwDataSize, &dwRead, &overlap))
			//theResult = HRESULT_FROM_WIN32(GetLastError());
			DWORD cbValid = min(STREAMING_BUFFER_SIZE, cbWaveSize - CurrentPosition);

			if (0 == ReadFile(theFile, buffers[CurrentDiskReadBuffer], STREAMING_BUFFER_SIZE, &dwRead, &overlap))
				theResult = HRESULT_FROM_WIN32(GetLastError());
			overlap.Offset += cbValid;

			//update the file position to where it will be once the read finishes
			CurrentPosition += cbValid;

			DWORD NumberBytesTransfered;
			GetOverlappedResult(theFile, &overlap, &NumberBytesTransfered, true);
		

			
			XAUDIO2_BUFFER buf = { 0 };
			if (myAudioBuffer.pAudioData == nullptr)
			{
				myAudioBuffer.AudioBytes = cbValid;
				myAudioBuffer.pAudioData = buffers[CurrentDiskReadBuffer];
				if (CurrentPosition >= cbWaveSize)
				{
					myAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
				}
				while (mySourceVoice->GetState(&state), state.BuffersQueued >= MAX_BUFFER_COUNT - 1)
				{
					WaitForSingleObject(myContext.hBufferEndEvent, INFINITE);

				}
				mySourceVoice->SubmitSourceBuffer(&myAudioBuffer);
			}
			else
			{
				buf.AudioBytes = cbValid;
				buf.pAudioData = buffers[CurrentDiskReadBuffer];
				if (CurrentPosition >= cbWaveSize)
				{
					buf.Flags = XAUDIO2_END_OF_STREAM;
				}
				while (mySourceVoice->GetState(&state), state.BuffersQueued >= MAX_BUFFER_COUNT - 1)
				{
					WaitForSingleObject(myContext.hBufferEndEvent, INFINITE);

				}
				mySourceVoice->SubmitSourceBuffer(&buf);
			}
			
			
			CurrentDiskReadBuffer++;
			CurrentDiskReadBuffer %= MAX_BUFFER_COUNT;
		}
	}
	
	myAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	mySourceVoice->SubmitSourceBuffer(&myAudioBuffer);
	while (state.BuffersQueued > 0)
	{
		mySourceVoice->GetState(&state);
		WaitForSingleObjectEx(myContext.hBufferEndEvent, INFINITE, TRUE);
	}
	if (FAILED(theResult = mySourceVoice->Stop(0, 0)))
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		return FAILURE;
	}

	DWORD dwRead;
	for (int i = 0; i < MAX_BUFFER_COUNT; i++)
	{
		if (INVALID_SET_FILE_POINTER == (ptrLocation = SetFilePointer(theFile, 0, NULL, FILE_BEGIN)))
			theResult = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(theFile, buffers[i], STREAMING_BUFFER_SIZE, &dwRead, &overlap))
			theResult = HRESULT_FROM_WIN32(GetLastError());
	}
	
	XAUDIO2_SEND_DESCRIPTOR send2 = { 0, mySourceVoice };
	XAUDIO2_VOICE_SENDS sendlist2 = { 1, &send2 };
	mySubmixVoice->SetOutputVoices(&sendlist2);
	isPlaying = false;
	isPaused = true;
}
GReturn WindowAppMusic::StreamStart()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (!isPlaying)
	{
		stopFlag = false;
		if (FAILED(theResult = mySourceVoice->Start(0, 0)))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = true;
		isPaused = false;

		//if can't find file for unit tests, use : _wgetcwd to see where to put test file 
		HANDLE theFile = myFile;

		if (INVALID_HANDLE_VALUE == theFile)
			theResult = HRESULT_FROM_WIN32(GetLastError());

		if (INVALID_SET_FILE_POINTER == SetFilePointer(theFile, 0, NULL, FILE_BEGIN))
			theResult = HRESULT_FROM_WIN32(GetLastError());


		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dataSize = 0;
		//checks the file type, expects a WAVE or XWMA
		//returns false otherwise
		theResult = FindChunk(theFile, fourRIFFcc, dwChunkSize, dwChunkPosition, dataSize);
		if (theResult != S_OK)
		{
			return FAILURE;
		}





		streamThread = new std::thread(&WindowAppMusic::Stream, this);

		//streamThread->detach();
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::PauseStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (!isPaused)
	{
		if (FAILED(theResult = mySourceVoice->Stop()))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = false;
		isPaused = true;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::ResumeStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	HRESULT theResult = S_OK;
	if (!isPlaying)
	{
		if (FAILED(theResult = mySourceVoice->Start()))
		{
			theResult = HRESULT_FROM_WIN32(GetLastError());
			return result;
		}
		isPlaying = true;
		isPaused = false;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::StopStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == NULL)
		return result;
	if (mySourceVoice == NULL)
		return result;
	result = REDUNDANT_OPERATION;
	if (streamThread == nullptr)
		return result;
	HRESULT theResult = S_OK;
	
	stopFlag = true;
	WaitForSingleObjectEx(myContext.hStreamEndEvent, INFINITE, TRUE);
	XAUDIO2_VOICE_STATE state;
	state.SamplesPlayed = 0;

	mySourceVoice->GetState(&state);


	streamThread->join();
theResult =	mySourceVoice->FlushSourceBuffers();
	isPlaying = false;
	isPaused = true;
	result = FAILURE;
	delete streamThread;
	streamThread = nullptr;





	result = SUCCESS;
	return result;
}
WindowAppMusic::~WindowAppMusic()
{

}
//End of GMusic implementation 
GReturn WindowAppAudio::Init(int _numOfOutputs)
{
	GReturn result = FAILURE;
	HRESULT theResult = CoInitialize(NULL);


	if (FAILED(theResult = XAudio2Create(&myAudio)))
	{
		return result;
	}
	if (FAILED(theResult = myAudio->CreateMasteringVoice(&theMasterVoice)))
	{
		return result;
	}
	numberOfOutputs = _numOfOutputs;
	result = SUCCESS;

	return result;
}

GReturn WindowAppAudio::CreateSound(const char* _path, GSound** _outSound)
{

	GReturn result = FAILURE;
	HRESULT theResult = S_OK;
	if (_outSound == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	WindowAppSound* snd = new WindowAppSound();

	if (snd == nullptr)
	{
		result = FAILURE;
		return result;
	}
	WAVEFORMATEXTENSIBLE wfmx;
	if (LoadWaveData(_path, wfmx, snd->myAudioBuffer) != S_OK)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}
	if (wfmx.Format.nChannels > maxChannels)
		maxChannels = wfmx.Format.nChannels;
	snd->myWFM = wfmx.Format;
	if (myAudio->CreateSubmixVoice(&snd->mySubmixVoice, numberOfOutputs, wfmx.Format.nSamplesPerSec) != S_OK)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}
	XAUDIO2_SEND_DESCRIPTOR sndSendDcsp = { 0, snd->mySubmixVoice };
	XAUDIO2_VOICE_SENDS sndSendList = { 1, &sndSendDcsp };
	if (myAudio->CreateSourceVoice(&snd->mySourceVoice, &snd->myWFM, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, &sndSendList) != S_OK)
	{
		theResult= HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}
	result = snd->Init();
	activeSounds.push_back(snd);
	snd->audio = this;
	*_outSound = snd;
	if (result == INVALID_ARGUMENT)
	{
		return result;
	}

	return result;
}
GReturn WindowAppAudio::CreateMusicStream(const char* _path, GMusic** _outMusic)
{
	GReturn result = FAILURE;
	HRESULT theResult = S_OK;
	if (_outMusic == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	WindowAppMusic* msc = new WindowAppMusic();

	if (msc == nullptr)
	{
		result = FAILURE;
		return result;
	}
	WAVEFORMATEXTENSIBLE wfmx;
	if (LoadOnlyWaveHeaderData(_path, msc->myFile, wfmx, msc->myAudioBuffer, msc->dataSize) != S_OK)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}
	if (wfmx.Format.nChannels > maxChannels)
		maxChannels = wfmx.Format.nChannels;
	msc->myWFM = wfmx.Format;
	
	if (myAudio->CreateSubmixVoice(&msc->mySubmixVoice, numberOfOutputs ,wfmx.Format.nSamplesPerSec ) != S_OK)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}
	XAUDIO2_SEND_DESCRIPTOR mscSendDcsp = { 0, msc->mySubmixVoice };
	XAUDIO2_VOICE_SENDS mscSendList= { 1, &mscSendDcsp };
	if (theResult = myAudio->CreateSourceVoice(&msc->mySourceVoice, &msc->myWFM,0, XAUDIO2_DEFAULT_FREQ_RATIO, &msc->myContext, &mscSendList) != S_OK)
	{
		theResult = HRESULT_FROM_WIN32(GetLastError());
		result = FAILURE;
		return result;
	}

	result = msc->Init();
	if (result != SUCCESS)
	{
		return result;
	}
	msc->audio = this;

	activeMusic.push_back(msc);
	*_outMusic = msc;
	if (result == INVALID_ARGUMENT)
		return result;

	return result;
}
GReturn WindowAppAudio::SetMasterVolume(float _value)
{
	GReturn result = INVALID_ARGUMENT;
	if (_value < 0.0)
	{
		return result;
	}
	result = SUCCESS;
	if (_value > 1.0)
	{
		maxVolume = 1.0;
	}
	else
	{
		maxVolume = _value;

	}
	return result;
}
GReturn WindowAppAudio::SetMasterChannelVolumes(const float * _values, int _numChannels)
{

	GReturn result = INVALID_ARGUMENT;
	if (_values == nullptr)
		return result;
	if (_numChannels < 0)
		return result;
	result = FAILURE;
	uint32_t theirChannels;
	for (int i = 0; i < activeSounds.size(); i++)
	{
		result = activeSounds[i]->GetChannels(theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
		result = activeSounds[i]->CheckChannelVolumes(_values, theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
	}
	for (int i = 0; i < activeMusic.size(); i++)
	{
		result = activeMusic[i]->GetChannels(theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
		result = activeMusic[i]->CheckChannelVolumes(_values, _numChannels);
		if (result != SUCCESS)
		{
			return result;
		}
	}
	return result;
}
GReturn WindowAppAudio::PauseAll()
{
	GReturn result = FAILURE;
	for (int i = 0; i < activeSounds.size(); i++)
	{
		result = activeSounds[i]->Pause();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	for (int i = 0; i < activeMusic.size(); i++)
	{
		result = activeMusic[i]->PauseStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	return result;
}
GReturn WindowAppAudio::StopAll()
{
	GReturn result = FAILURE;
	for (int i = 0; i < activeSounds.size(); i++)
	{
		result = activeSounds[i]->StopSound();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	for (int i = 0; i < activeMusic.size(); i++)
	{
		result = activeMusic[i]->StopStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	return result;
}
GReturn WindowAppAudio::ResumeAll()
{
	GReturn result = FAILURE;
	for (int i = 0; i < activeSounds.size(); i++)
	{
		result = activeSounds[i]->Resume();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	for (int i = 0; i < activeMusic.size(); i++)
	{
		result = activeMusic[i]->ResumeStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	return result;
}
WindowAppAudio::~WindowAppAudio()
{
	while(activeSounds.size() > 0)
	{
		activeSounds.erase(activeSounds.begin());
	}
	while (activeMusic.size() > 0)
	{
		activeMusic.erase(activeMusic.begin());
	}
	
}





//Start of GAudio implementation for Windows
GReturn PlatformGetAudio(GAudio ** _outAudio)
{
	GReturn result = FAILURE;
	if (_outAudio == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	WindowAppAudio* audio = new WindowAppAudio();

	if (audio == nullptr)
	{
		result = FAILURE;
		return result;
	}
	audio->Init();

	if (result == INVALID_ARGUMENT)
		return result;

	*_outAudio = audio;
	result = SUCCESS;
	return result;
}
//End of GMusic implementation for Windows 
