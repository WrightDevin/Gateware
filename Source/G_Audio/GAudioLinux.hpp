// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

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

class WindowAppAudio;
class WindowAppSound : public GSound
{
public:
	int index = -1;
	WindowAppAudio * audio;

	bool loops = false;
	bool isPlaying = false;
	bool isPaused = false;
	float volume = 1.0f;
	GReturn Init();
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn CheckChannelVolumes(const float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn GetChannels(unsigned int & returnedChannelNum );
	GReturn Play();
	GReturn Pause();
	GReturn Resume();
	GReturn StopSound();
	~WindowAppSound();
};

class WindowAppMusic : public GMusic
{
private:
	unsigned int buffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE];

public:
	char * myFile;
	int index = -1;
	unsigned long dataSize;
	WindowAppAudio * audio;
	
//	WAVEFORMATEX myWFM = {0};
//	std::thread* streamThread = nullptr;
//	XAUDIO2_BUFFER myAudioBuffer = { 0 };

	bool loops = false;
	bool isPlaying = false;
	bool isPaused = false;
	bool stopFlag = false;
	float volume = 1.0f;
	GReturn Init();
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn CheckChannelVolumes(const float *_values, int _numChannels);
	GReturn GetChannels(unsigned int & returnedChannelNum);
	GReturn SetVolume(float _newVolume);
	GReturn StreamStart();
	GReturn Stream();
	GReturn PauseStream();
	GReturn ResumeStream();
	GReturn StopStream();
	~WindowAppMusic();


	
};


class WindowAppAudio : public GAudio
{
public:
	const char * myFile;
	//std::vector<WindowAppSound *> activeSounds;
	//std::vector<WindowAppMusic *> activeMusic;

	float maxVolume;
	int maxChannels;

	GReturn Init();
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

	return result;
}
GReturn WindowAppSound::SetPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn WindowAppSound::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;
	
	if (_values == nullptr)
		return result;
	result = GReturn::FAILURE;
	for (int i = 0; i < _numChannels; i++)
	{
		//try
		{
			if (_values[i] > audio->maxVolume)
			{
				_values[i] = audio->maxVolume;
			}
		}
	

	}

	//if (FAILED(theResult = mySourceVoice->SetChannelVolumes(_numChannels, _values)))

	return result;
}
GReturn WindowAppSound::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;
	
	if (_values == nullptr)
		return result;

	unsigned int currentChannels;
	result = GetChannels(currentChannels);
	if (result != SUCCESS)
		return result;
	float * currentValues = new float[currentChannels];
	
//	mySourceVoice->GetChannelVolumes(_numChannels, currentValues);
	if (currentValues == nullptr)
		return result;

	bool didChange = false;
	for (int i = 0; i < _numChannels; i++)
	{
		//try
		{
			if (currentValues[i] > _values[i])
			{
				currentValues[i] = _values[i];
				didChange = true;
			}
		}
	}

	

	if (didChange == true)
	{
	
	}

	return result;
}
GReturn WindowAppSound::GetChannels(unsigned int & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
	{
		return result;
	}
//	returnedChannelNum = myWFM.nChannels;
//	result = SUCCESS;
	return result;
}
GReturn WindowAppSound::SetVolume(float _newVolume)
{
	GReturn result = INVALID_ARGUMENT;
	if (_newVolume < 0.0f)
		return result;
	result = SUCCESS;
	if (audio == nullptr)
		return result;



	if (_newVolume > audio->maxVolume)
	{
		_newVolume = audio->maxVolume;
	}


	return result;
}
GReturn WindowAppSound::Play()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
	
	if (!isPlaying)
	{
		
	//	isPlaying = true;
	//	isPaused = false;
	}
	//result = SUCCESS;
	return result;
}
GReturn WindowAppSound::Pause()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	if (!isPaused)
	{
	//TODO insert code
		isPlaying = false;
		isPaused = true;
	}
	//result = SUCCESS;
	return result;

}
GReturn WindowAppSound::Resume()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	
	if (!isPlaying)
	{
	
		isPlaying = true;
		isPaused = false;
	}
	//result = SUCCESS;
	return result;
}
GReturn WindowAppSound::StopSound()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
	


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
	if (audio == nullptr)
		return result;
	
	if (_values == nullptr)
		return result;
	result = FAILURE;
	for (int i = 0; i < _numChannels; i++)
	{
		//try
		{
			if (_values[i] > audio->maxVolume)
			{
				_values[i] = audio->maxVolume;
			}
		}
	

	}

	return result;
}
GReturn WindowAppMusic::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;

	if (_values == nullptr)
		return result;

	result = FAILURE;
	unsigned int currentChannels;
	result = GetChannels(currentChannels);
	if (result != SUCCESS)
		return result;
	float * currentValues = new float [currentChannels];

	if (currentValues == nullptr)
		return result;

	bool didChange = false;
	for (int i = 0; i < _numChannels; i++)
	{
		//try
		{
			if (currentValues[i] > _values[i])
			{
				currentValues[i] = _values[i];
				didChange = true;
			}
		}
	

	}
	
	if (didChange == true)
	{
		
	}
	
	return result;
}
GReturn WindowAppMusic::GetChannels(unsigned int & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
	{
		return result;
	}
	result = INVALID_ARGUMENT;
	if (returnedChannelNum <= 0)
		return result;
//	returnedChannelNum = myWFM.nChannels;
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::SetVolume(float _newVolume)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
		return result;

	result = INVALID_ARGUMENT;
	if (_newVolume < 0.0f)
		return result;
	result = FAILURE;
	if (_newVolume > audio->maxVolume)
	{
		_newVolume = audio->maxVolume;
	}

	result = SUCCESS;

	return result;
}
GReturn WindowAppMusic::Stream()
{
}
GReturn WindowAppMusic::StreamStart()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
	

	if (!isPlaying)
	{
		stopFlag = false;
		
		isPlaying = true;
		isPaused = false;

		//if can't find file for unit tests, use : _wgetcwd to see where to put test file 
	
		//checks the file type, expects a WAVE or XWMA
		//returns false otherwise
	




		//streamThread = new std::thread(&WindowAppMusic::Stream, this);

		//streamThread->detach();
	}
	//result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::PauseStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
		return result;
	
	if (!isPaused)
	{
		
		isPlaying = false;
		isPaused = true;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::ResumeStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	
	if (!isPlaying)
	{
		
		isPlaying = true;
		isPaused = false;
	}
	result = SUCCESS;
	return result;
}
GReturn WindowAppMusic::StopStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	//if (streamThread == nullptr)
		//return result;
	
	stopFlag = true;
	//streamThread->join();
	
	isPlaying = false;
	isPaused = true;

	result = SUCCESS;
	return result;
}
WindowAppMusic::~WindowAppMusic()
{

}
//End of GMusic implementation 
GReturn WindowAppAudio::Init()
{
	GReturn result = FAILURE;
	

	return result;
}
GReturn WindowAppAudio::CreateSound(const char* _path, GSound** _outSound)
{

	GReturn result = FAILURE;
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
	//TODO load sound data here
	result = snd->Init();
	//activeSounds.push_back(snd);
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
	//TODO load music data here

	result = msc->Init();
	if (result != SUCCESS)
	{
		return result;
	}
	msc->audio = this;

	//activeMusic.push_back(msc);
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
	unsigned int theirChannels;
//	for (int i = 0; i < activeSounds.size(); i++)
	{
		//result = activeSounds[i]->GetChannels(theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
		//result = activeSounds[i]->CheckChannelVolumes(_values, theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
	}
//	for (int i = 0; i < activeMusic.size(); i++)
	{
		//result = activeMusic[i]->GetChannels(theirChannels);
		if (result != SUCCESS)
		{
			return result;
		}
	//	result = activeMusic[i]->CheckChannelVolumes(_values, _numChannels);
		if (result != SUCCESS)
		{
			return result;
		}
	}
	result = FAILURE;
	return result;
}
GReturn WindowAppAudio::PauseAll()
{
	GReturn result = FAILURE;
	//for (int i = 0; i < activeSounds.size(); i++)
	{
		//result = activeSounds[i]->Pause();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	//for (int i = 0; i < activeMusic.size(); i++)
	{
		//result = activeMusic[i]->PauseStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	result = FAILURE;
	return result;
}
GReturn WindowAppAudio::StopAll()
{
	GReturn result = FAILURE;
//	for (int i = 0; i < activeSounds.size(); i++)
	{
		//result = activeSounds[i]->StopSound();
		if (result != SUCCESS)
		{
			return result;
		}
	}
//	for (int i = 0; i < activeMusic.size(); i++)
	{
		//result = activeMusic[i]->StopStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	result = FAILURE;
	return result;
}
GReturn WindowAppAudio::ResumeAll()
{
	GReturn result = FAILURE;
	//for (int i = 0; i < activeSounds.size(); i++)
	{
		//result = activeSounds[i]->Resume();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	//for (int i = 0; i < activeMusic.size(); i++)
	{
		//result = activeMusic[i]->ResumeStream();
		if (result != SUCCESS)
		{
			return result;
		}
	}
	result = FAILURE;
	return result;
}
WindowAppAudio::~WindowAppAudio()
{

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
