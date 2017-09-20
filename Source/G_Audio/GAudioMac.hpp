
// Override export symbols for DLL builds (must be included before interface code).
#include "../DLL_Export_Symbols.h"

#include "../../Interface/G_Audio/GAudio.h"

using namespace GW;
using namespace AUDIO;

class MacAppAudio;
class MacAppSound : public GSound
{
public:
	int index = -1;
	MacAppAudio * audio;

	bool loops = false;
	bool isPlaying = false;
	bool isPaused = false;
	float volume = 1.0f;
	GReturn Init();
	GReturn SetPCMShader(const char* _data);
	GReturn SetChannelVolumes(float *_values, int _numChannels);
	GReturn CheckChannelVolumes(const float *_values, int _numChannels);
	GReturn SetVolume(float _newVolume);
	GReturn GetChannels(unsigned int & returnedChannelNum);
	GReturn Play();
	GReturn Pause();
	GReturn Resume();
	GReturn StopSound();
	~MacAppSound();
#if __APPLE__
	GMacSound * mac_snd = nullptr;
#endif
};

class MacAppMusic : public GMusic
{
private:
	char buffers[3][65543];
	//OVERLAPPED overlap = { 0 };
public:
	char * myFile;
	int index = -1;
	unsigned long dataSize;
	MacAppAudio * audio;
	
	//std::thread* streamThread = nullptr;


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
	~MacAppMusic();

#if __APPLE__
	GMacMusic * mac_msc = nullptr;
#endif

};


class MacAppAudio : public GAudio
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
	~MacAppAudio();

#if __APPLE__
	GMacAudio * mac_audio = nullptr;
#endif
};
//Start of GSound implementation 
GReturn MacAppSound::Init()
{
	GReturn result = GReturn::FAILURE;

	return result;
}
GReturn MacAppSound::SetPCMShader(const char* _data)
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppSound::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = GReturn::INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppSound::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::FAILURE;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppSound::GetChannels(unsigned int & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
	{
		return result;
	}

	return result;
}
GReturn MacAppSound::SetVolume(float _newVolume)
{
	GReturn result = INVALID_ARGUMENT;
	if (_newVolume < 0.0f)
		return result;
	result = SUCCESS;
	if (audio == nullptr)
		return result;
#if __APPLE__
	bool bresult = [mac_snd SetVolume : _newVolume];
	if (bresult == true)
		result = SUCCESS;
	else
		result = FAILURE;
#endif
	return result;
}
GReturn MacAppSound::Play()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
#if __APPLE__
	bool bresult = [mac_snd PlaySound];
	if (bresult == true)
		result = SUCCESS;
	else
		result = FAILURE;

#endif
	return result;
}
GReturn MacAppSound::Pause()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
#if __APPLE__
	bool bresult = [mac_snd PauseSound];
	if (bresult == true)
		result = SUCCESS;
	else
		result = FAILURE;

#endif
	return result;

}
GReturn MacAppSound::Resume()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
#if __APPLE__
	bool bresult = [mac_snd ResumeSound];
	if (bresult == true)
		result = SUCCESS;
	else
		result = FAILURE;

#endif
	return result;
}
GReturn MacAppSound::StopSound()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
#if __APPLE__
	bool bresult = [mac_snd StopSound];
	if (bresult == true)
		result = SUCCESS;
	else
		result = FAILURE;
#endif

	return result;
}
MacAppSound::~MacAppSound()
{


}
//End of GSound implementation

//Start of GMusic implementation
GReturn MacAppMusic::Init()
{
	GReturn result = GReturn::FAILURE;
#if __APPLE__

	NSString * nsPath = [[[NSString alloc] initWithUTF8String:_path] autorelease];
	mac_snd = [[GMacSound alloc]initWithPath:nsPath];
	
	if (_outSoundData != nullptr)
	{
		result = SUCCESS;
	}
	else
	{
		result = FAILURE;
	}
#endif
	return result;
}
GReturn MacAppMusic::SetPCMShader(const char* _data)
{
	GReturn result = FAILURE;

	return result;
}
GReturn MacAppMusic::SetChannelVolumes(float * _values, int _numChannels)
{
	GReturn result = INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppMusic::CheckChannelVolumes(const float * _values, int _numChannels)
{
	GReturn result = GReturn::INVALID_ARGUMENT;
	if (_numChannels <= 0)
		return result;
	if (audio == nullptr)
		return result;
	
	return result;
}
GReturn MacAppMusic::GetChannels(unsigned int & returnedChannelNum)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
	{
		return result;
	}
	
	return result;
}
GReturn MacAppMusic::SetVolume(float _newVolume)
{
	GReturn result = FAILURE;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppMusic::Stream()
{

}
GReturn MacAppMusic::StreamStart()
{
	GReturn result = GReturn::FAILURE;
	
	return result;
}
GReturn MacAppMusic::PauseStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;
	
	return result;
}
GReturn MacAppMusic::ResumeStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	return result;
}
GReturn MacAppMusic::StopStream()
{
	GReturn result = GReturn::FAILURE;
	if (audio == nullptr)
		return result;

	return result;
}
MacAppMusic::~MacAppMusic()
{

}
//End of GMusic implementation 
GReturn MacAppAudio::Init()
{
	GReturn result = FAILURE;

	result = SUCCESS;

	return result;
}
GReturn MacAppAudio::CreateSound(const char* _path, GSound** _outSound)
{

	GReturn result = FAILURE;
	if (_outSound == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	MacAppSound* snd = new MacAppSound();

	if (snd == nullptr)
	{
		result = FAILURE;
		return result;
	}
	
	result = snd->Init();
//	activeSounds.push_back(snd);
	snd->audio = this;
	*_outSound = snd;
	if (result == INVALID_ARGUMENT)
	{
		return result;
	}

	return result;
}
GReturn MacAppAudio::CreateMusicStream(const char* _path, GMusic** _outMusic)
{
	GReturn result = FAILURE;
	
	if (_outMusic == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	MacAppMusic* msc = new MacAppMusic();

	if (msc == nullptr)
	{
		result = FAILURE;
		return result;
	}


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
GReturn MacAppAudio::SetMasterVolume(float _value)
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
GReturn MacAppAudio::SetMasterChannelVolumes(const float * _values, int _numChannels)
{

	GReturn result = INVALID_ARGUMENT;
	if (_values == nullptr)
		return result;
	if (_numChannels < 0)
		return result;
	result = FAILURE;

	return result;
}
GReturn MacAppAudio::PauseAll()
{
	GReturn result = FAILURE;
	
	return result;
}
GReturn MacAppAudio::StopAll()
{
	GReturn result = FAILURE;
	
	return result;
}
GReturn MacAppAudio::ResumeAll()
{
	GReturn result = FAILURE;

	return result;
}
MacAppAudio::~MacAppAudio()
{

}


//Start of GAudio implementation for Macs
GReturn PlatformGetAudio(GAudio ** _outAudio)
{
	GReturn result = FAILURE;
	if (_outAudio == nullptr)
	{
		result = INVALID_ARGUMENT;
		return result;
	}
	MacAppAudio* audio = new MacAppAudio();

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


